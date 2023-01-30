/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */

/*        STARTSINGLE_OF_MULTIPLE_COMMENT      */

/*****************************************************************************
| Project Name: Autosar CAN driver
|    File Name: Can.h
|  Description: API to hardware abstraction of the CAN-driver
|               Version only changed when API change done (change on subversions
|               are not mentioned in history)
|-----------------------------------------------------------------------------
|               C O P Y R I G H T
|-----------------------------------------------------------------------------
| Copyright (c) 2005-2012 by Vector Informatik GmbH.      All rights reserved.
| This software is copyright protected and proprietary 
| to Vector Informatik GmbH. Vector Informatik GmbH 
| grants to you only those rights as set out in the 
| license conditions. All other rights remain with 
| Vector Informatik GmbH.
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Bir          Holger Birke              Vector Informatik GmbH
| Tvi          Timo Vanoni               Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               API  R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver      Author    Description
| ----------  -------  --------- ---------------------------------------------
| 2005-09-15  0.01.00  Bir       - initial version
| 2006-05-22  2.00.00  Bir       - Support for AutoSar 2.0
|                                  can.h and can_types.h connected
| 2006-06-23  2.01.00  Bir       - define for MEMORY_ROM (compatibility)
| 2006-06-23  2.02.00  Bir       - remove Can_HwHandleType from indication / define as uint8
| 2006-09-04  2.03.00  Bir       - length of ControllerName expand to 20 characters
| 2006-09-25  2.04.00  Bir       - Add API for Polling
| 2006-11-15  2.05.00  Bir       - Add postbuild
|                                - ESCAN00018915: Change multiple-include define
| 2006-11-15  2.06.00  Bir       - Support "Can_MainFunction_BusOff"
| 2007-03-09  2.07.00  Bir       - ESCAN00019889: Update to ASR2.1.0
|                                - suppress multiplicity by organi
| 2007-07-03  2.08.00  Bir       - Move all version defines from Proto.h to CAN.h (licence scanning)
|                                - Add CAN_AR_*_VERSION
|                                - remove PduId out of mailbox (old from CANIf)
|                                - move multichannel api define to here
|                                - set "C_ENABLE_OSEK_OS_INTCAT2" if not defined "C_ENABLE_INT_OSCAT1"
| 2007-10-15  2.09.00  Bir       - ESCAN00022773: use of #ifndef instead of #if !defined
| 2007-10-31  2.10.00  Bir       - ESCAN00023049: Change API can_init() to one para, add const in Can_InitController()
|                                -                Add API to set this 2nd para as Baudrate change (Can_InitStruct)
|                                - add v_def.h include (remove define of V_MEM..)
| 2007-10-15  2.11.00  Bir       - ESCAN00023442: Change Id type
| 2008-02-06  3.00.00  Bir       - ESCAN00024406: ASR3.0
| 2008-04-16  3.01.00  Bir       - ESCAN00026087: Case sensitive naming for all File names (and includes)
| 2008-05-19  3.02.00  Bir       - Move include section to top of file (need before version defines)
| 2008-05-19  3.03.00  Bir       - (see ESCAN 29839) Change naming: "INTERRUPT" and "POLLING" add prefix "CAN_*"
|                                - (see ESCAN 29826) Remove include of v_cfg.h and v_def.h (will be generated)
|                                - ESCAN00030521: Linker error because of missing Interrupt service routine
| 2008-10-23  3.04.00  Bir       - ESCAN00029129: API for HW loop timer
| 2009-04-20  3.05.00  Bir       - ESCAN00034118: Add compiler abstraction
|                                - ESCAN00034119: Add memory abstraction
| 2009-08-24  3.05.01  Bir       - ESCAN00037276: Compiler warning "function declared implicitly"
| 2009-09-15  3.06.00  Bir       - ESCAN00037784: Add Generic Confirmation function
| 2010-01-19  3.06.01  Bir       - ESCAN00040258: Use Can_HwHandleType instead of uint8 for Can_Write()
| 2010-03-09  3.06.02  Bir       - ESCAN00041432: Declaration for ISRs missing in case of Full Polling with Indiv Polling
| 2010-05-31  3.07.00  Bir       - ESCAN00043224: New API Can_GetStatus()
|                                - ESCAN00043250: Add Application Interrupt lock functions
| 2010-11-23  3.08.00  Bir       - ESCAN00043999: Support usage without v_def.h
| 2011-03-11  4.00.00  Bir       - ESCAN00043688: Support Autosar 4.0 R1
|                                - ESCAN00044010: Add Notification for Overrun detection
|                                - ESCAN00047111: Add Notification for RAM Check
| 2011-04-04  4.00.01  Bir       - ESCAN00049613: AR Version is not correct (2.2.0 instead of 2.2.1)
| 2011-06-21  4.01.00  Bir       - ESCAN00050960: Provide API for Generic Pretransmit (AR3-1654 )
|                                - ESCAN00054813: Add Mirror functionality
| 2011-06-21  4.01.01  Bir       - ESCAN00056004: Add Code Traceability to AutoSar SWS
| 2012-01-20  4.01.02  Bir       - ESCAN00056185: Change Version Check
| 2012-06-04  4.01.03  Bir       - ESCAN00059265: Compiler error: hardware loop index is not available as define for API
| 2012-06-12  4.02.00  Bir       - ESCAN00059412: AR4-135: support MSR 4 R5
| 2012-06-12  4.02.01  Bir       - move some gobal compatibility defines from proto.h to can.h
| 2013-06-12  4.03.00  Tvi/Bir   - ESCAN00069107: AR4-397: Implement supporrt for CAN-FD according to ASR4.1.1
|***************************************************************************/
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

#if !defined(CAN_H)
#define CAN_H

/***************************************************************************/
/* Include                                                                 */
/***************************************************************************/
/* CAN034 */
#include "Can_Cfg.h"

#if !defined(CAN_MIRROR_MODE)
# define CAN_MIRROR_MODE STD_OFF
#else
# if (CAN_MIRROR_MODE == STD_ON)
#  include "CDDMirror.h"
#  define C_ENABLE_MIRROR_MODE
# endif
#endif

/* PRQA  S 0828 QAC_Can_0828 */ /* MD_Can_0828 */
/* PRQA  S 0850 QAC_Can_0850 */ /* MD_Can_0850 */

/***************************************************************************/
/* Version                  (abcd: Main version ab Sub Version cd )        */
/***************************************************************************/
/* Vector module version */
/* ##V_CFG_MANAGEMENT ##CQProject : DrvCan_Tms470DcanAsr CQComponent : Implementation */
#define DRVCAN_TMS470DCANASR_VERSION 0x0123U
#define DRVCAN_TMS470DCANASR_RELEASE_VERSION 0x00

/* internal Version of the CAN.h API file */
#define DRVCAN_APIASR_VERSION             0x0403u
#define DRVCAN_APIASR_RELEASE_VERSION     0x00u

/* AutoSar Version for API */
/* CAN085, BR:013, BR:014 */
#if !defined(CAN_MSR403)
# define CAN_MSR403                       403u
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
# define CAN_AR_RELEASE_MAJOR_VERSION      4
# define CAN_AR_RELEASE_MINOR_VERSION      0
# define CAN_AR_RELEASE_REVISION_VERSION   1
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR403)
# define CAN_AR_RELEASE_MAJOR_VERSION      4
# define CAN_AR_RELEASE_MINOR_VERSION      0
# define CAN_AR_RELEASE_REVISION_VERSION   3
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR30)
# define CAN_AR_MAJOR_VERSION              2
# define CAN_AR_MINOR_VERSION              5
# define CAN_AR_PATCH_VERSION              0
#endif

/* AutoSar module version */
#define CAN_SW_MAJOR_VERSION   ((uint8)((DRVCAN_TMS470DCANASR_VERSION & 0xFF00u) >> 8))
#define CAN_SW_MINOR_VERSION   ((uint8)(DRVCAN_TMS470DCANASR_VERSION & 0x00FFu))
#if (DRVCAN_APIASR_RELEASE_VERSION   == 0xFFu)
/* This is a develop version and should not be deliverd */
# define CAN_SW_PATCH_VERSION  ((uint8)0xFFu)
#else
# define CAN_SW_PATCH_VERSION  ((uint8)(DRVCAN_TMS470DCANASR_RELEASE_VERSION & 0xFFu))
#endif

/***************************************************************************/
/* Defines and Macros                                                      */
/***************************************************************************/
#define CAN_VENDOR_ID   30u
#define CAN_MODULE_ID   80u
#define CAN_INSTANCE_ID  0u

#if (CAN_MICROSAR_VERSION != CAN_MSR403) /* otherwise enum in Can_GeneralTypes */
/* Can_SetControllerMode transient */
# define CAN_T_START       0
# define CAN_T_STOP        1
# define CAN_T_SLEEP       2
# define CAN_T_WAKEUP      3
/* return values (e.g. for Can_SetControllerMode) */
/* CAN039 */
# define CAN_NOT_OK        (uint8)0x00
# define CAN_OK            (uint8)0x01
# define CAN_NOT_SUPPORTED ((uint8)0x02 | CAN_OK) /* not supported is ok + special bit for internal use -> used for Sleep/wakeup mask out 0x02 to get CAN_OK */
# define CAN_REQUESTED     (uint8)0x04
/* return values for Can_write */
#endif
#define CAN_FREE           CAN_OK              /* none AUTOSAR (used only internal) */
#define CAN_BUSY           CAN_NOT_SUPPORTED   /* none AUTOSAR (used only internal) */

#if !defined (kCanChannelNotUsed)
# define kCanChannelNotUsed 0xFF
#endif

/* Module Id's */
#define CAN_INIT_ID            0x00
#define CAN_INITCTR_ID         0x02
#define CAN_SETCTR_ID          0x03
#define CAN_DIINT_ID           0x04
#define CAN_ENINT_ID           0x05
#define CAN_WRITE_ID           0x06
#define CAN_VERSION_ID         0x07
#define CAN_MAINFCT_WRITE_ID   0x01
#define CAN_MAINFCT_READ_ID    0x08
#define CAN_MAINFCT_BO_ID      0x09
#define CAN_MAINFCT_WU_ID      0x0A
#define CAN_MAINFCT_MODE_ID    0x0C
#define CAN_CKWAKEUP_ID        0x0B
#define CAN_CHANGE_BR_ID       0x0D
#define CAN_CHECK_BR_ID        0x0E
#define CAN_SET_BR_ID          0x0F

/* Internal Id's */
#define CAN_RXINDI_ID          0x10
#define CAN_TXCNF_ID           0x11
#define CAN_CTRWAKEUP_ID       0x12
#define CAN_CTRBUSOFF_ID       0x13
#define CAN_HW_ACCESS_ID       0x20

/* CAN104, CAN080  Error Codes */
#define CAN_E_PARAM_POINTER         (uint8)0x01
#define CAN_E_PARAM_HANDLE          (uint8)0x02
#define CAN_E_PARAM_DLC             (uint8)0x03
#define CAN_E_PARAM_CONTROLLER      (uint8)0x04
#define CAN_E_UNINIT                (uint8)0x05
#define CAN_E_TRANSITION            (uint8)0x06
#define CAN_E_DATALOST              (uint8)0x07   /* for MSR30 extension */
#define CAN_E_PARAM_BAUDRATE        (uint8)0x08   /* MRS403 only */
#define CAN_E_RXQUEUE               (uint8)0x10   /* extension */
#define CAN_E_TIMEOUT_DET           (uint8)0x11   /* extension */

/* Return values Can_GetStatus() */
#define CAN_STATUS_UNINIT                       ((uint8)0x00) /* ASR extension */
#define CAN_STATUS_START                        ((uint8)0x01) /* ASR extension (kCanTxOn) */
#define CAN_STATUS_STOP                         ((uint8)0x02) /* kCanHwIsStop */
#define CAN_STATUS_INIT                         ((uint8)0x04) /* kCanHwIsInit */
#define CAN_STATUS_INCONSISTENT                 ((uint8)0x08) /* kCanHwIsInconsistent      used for common CAN */
#define CAN_STATUS_WARNING                      ((uint8)0x10) /* kCanHwIsWarning */
#define CAN_STATUS_PASSIVE                      ((uint8)0x20) /* kCanHwIsPassive */
#define CAN_STATUS_BUSOFF                       ((uint8)0x40) /* kCanHwIsBusOff */
#define CAN_STATUS_SLEEP                        ((uint8)0x80) /* kCanHwIsSleep */
#if defined( C_DRV_INTERNAL ) /* just for internal usage */
# define CAN_STATUS_WAKEUP                       ((uint8)0x08) /* only for Request State: parallel to CAN_STATUS_INCONSISTENT */
# define CAN_STATUS_SETMODE                      ((uint8)0x04) /* only for Request State: parallel to CAN_STATUS_INIT */
#endif
/* Macros to use Can_GetStatus() */
#define CanHwIsOk(state)                        (((state) & (CAN_STATUS_WARNING |  \
                                                             CAN_STATUS_PASSIVE |  \
                                                             CAN_STATUS_BUSOFF) )    == 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsWarning(state)                   (((state) & CAN_STATUS_WARNING)      != 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsPassive(state)                   (((state) & CAN_STATUS_PASSIVE)      != 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsBusOff(state)                    (((state) & CAN_STATUS_BUSOFF)       != 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsWakeup(state)                    (((state) & CAN_STATUS_SLEEP)        == 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsSleep(state)                     (((state) & CAN_STATUS_SLEEP)        != 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsStop(state)                      (((state) & CAN_STATUS_STOP)         != 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsStart(state)                     (((state) & CAN_STATUS_START)        != 0) /* PRQA S 3453 */ /* MD_Can_3453 */
#define CanHwIsInconsistent(state)              (((state) & CAN_STATUS_INCONSISTENT) != 0) /* PRQA S 3453 */ /* MD_Can_3453 */

/* Hardware Loop defines */
#if (CAN_MICROSAR_VERSION != CAN_MSR30)
# define kCanLoopStart        ((uint8)CAN_LOOP_MAX)  /* used by HL */
# define kCanLoopStop         ((uint8)CAN_LOOP_MAX)  /* used by HL */
# define kCanLoopSleep        ((uint8)CAN_LOOP_MAX)  /* used by HL */
# define kCanLoopWakeup       ((uint8)CAN_LOOP_MAX)  /* used by HL */
#else
/* defined by LL */
#endif
/* parameter for ApplCanTimerStart(),-End(), -Loop()*/
/* index has to start with 0, continues numbers have to be used. Gabs are not 
   allowed! */
#define kCanLoopIrqReq          0x00U
#define kCanLoopBusyReq         0x01U
#define kCanLoopSleepReq        0x02U

# if (CAN_MICROSAR_VERSION == CAN_MSR30)
#   define kCanLoopSleep        ((vuint8)0x03U)  /* used by core */
#   define kCanLoopWakeup       ((vuint8)0x04U)  /* used by core */
# else
/* CAN_MSR40 use CAN_LOOP_MAX for internal loop index */
# endif

/* compatibility */
#define kCanHwIsInit CAN_STATUS_INIT
#define kCanHwIsSleep CAN_STATUS_SLEEP
/* results of CAN RAM check */
#define kCanRamCheckFailed                      CAN_NOT_OK
#define kCanRamCheckOk                          CAN_OK
#define CAN_DEACTIVATE_CONTROLLER               CAN_STATUS_INCONSISTENT
#define CAN_ACTIVATE_CONTROLLER                 ((uint8)0x00)

/* compatibility to LL in can_irq.c / can.c */
#if defined(V_OSTYPE_OSEK) || defined(V_OSTYPE_AUTOSAR)
# if !defined(C_ENABLE_OSEK_OS)
#  define C_ENABLE_OSEK_OS
# endif
# if !defined( C_ENABLE_OSEK_OS_INTCAT2 ) && !defined( C_DISABLE_OSEK_OS_INTCAT2 )
#  define C_ENABLE_OSEK_OS_INTCAT2
# endif
#endif
#if ( CAN_TX_PROCESSING == CAN_POLLING )
# define C_ENABLE_TX_POLLING
#endif
#if ( CAN_RX_PROCESSING == CAN_POLLING )
# define C_ENABLE_RX_BASICCAN_POLLING
# define C_ENABLE_RX_FULLCAN_POLLING
# define C_ENABLE_RX_POLLING
#endif
#if ( CAN_BUSOFF_PROCESSING == CAN_POLLING )
# define C_ENABLE_ERROR_POLLING
#endif
#if ( CAN_WAKEUP_PROCESSING == CAN_POLLING )
# define C_ENABLE_WAKEUP_POLLING
#endif
#if ( CAN_INDIVIDUAL_PROCESSING == STD_ON )
# define C_ENABLE_INDIVIDUAL_POLLING
#endif
#if ( CAN_MULTIPLE_BASICCAN == STD_ON )
# define C_ENABLE_MULTIPLE_BASICCAN
#endif
#if (CAN_TX_FULLCAN_OBJECTS == STD_ON)
# define C_ENABLE_TX_FULLCAN_OBJECTS
#endif
#if (CAN_RX_FULLCAN_OBJECTS == STD_ON)
# define C_ENABLE_RX_FULLCAN_OBJECTS
#endif
#if (CAN_RX_BASICCAN_OBJECTS == STD_ON)
# define C_ENABLE_RX_BASICCAN_OBJECTS
#endif
#if (CAN_MULTI_ECU_CONFIG == STD_ON)
#define C_ENABLE_MULTI_ECU_CONFIG
#endif
#if (CAN_HW_TRANSMIT_CANCELLATION == STD_ON)
# define C_ENABLE_CANCEL_IN_HW
#endif
#if (CAN_HARDWARE_CANCELLATION == STD_ON)
#define C_ENABLE_HW_LOOP_TIMER
#endif
#if ( CAN_EXTENDED_ID == STD_ON)
# define C_ENABLE_EXTENDED_ID
#endif
#if ( CAN_MIXED_ID == STD_ON)
# define C_ENABLE_MIXED_ID
#endif
#if ( CAN_SECURE_TEMP_BUFFER == STD_ON )
# define C_ENABLE_HWBUFFER
#endif
#if (CAN_SLEEP_SUPPORT == STD_ON) && (CAN_WAKEUP_SUPPORT == STD_ON)
/* before version 3.12 this switches occur always syncron both to ON or OFF (C_ENABLE_WAKEUP no more used) */
/* if CAN_WAKEUP_SUPPORT is switched off, stop mode will be used instead of sleep (see Autosar spec) */
# define C_ENABLE_SLEEP_WAKEUP
#endif
#if defined( CAN_COMMON_CAN )
# if ( CAN_COMMON_CAN == STD_ON )
#  define C_ENABLE_COMMON_CAN
# else
#  define C_DISABLE_COMMON_CAN
# endif
#else
# define C_DISABLE_COMMON_CAN
#endif
/* compatibility to older baseAsr.dll */
#if defined(CAN_RX_QUEUE)
# if (CAN_RX_QUEUE == STD_ON)
#  define C_ENABLE_RX_QUEUE
# endif
#else
# define CAN_RX_QUEUE STD_OFF
#endif
#if !defined(CAN_GENERIC_CONFIRMATION)
# define CAN_GENERIC_CONFIRMATION            STD_OFF
#endif
#if !defined(CAN_DYNAMIC_FULLCAN_ID)
#define CAN_DYNAMIC_FULLCAN_ID               STD_ON
#endif
#if !defined(CAN_ONE_CONTROLLER_OPTIMIZATION)
#define CAN_ONE_CONTROLLER_OPTIMIZATION      STD_OFF
#endif
#if ( CAN_ONE_CONTROLLER_OPTIMIZATION == STD_ON )
# if defined(kCanNumberOfMaxUsedControllers)
#  if (kCanNumberOfMaxUsedControllers != 1)
#   error "Using Optimization for one Controller does not work with more than 1 Controller (max) configured"
#  endif
# endif
# define C_SINGLE_RECEIVE_CHANNEL
# define C_DISABLE_MULTICHANNEL_API
# define CAN_CHANNEL_CANTYPE_ONLY         void   /* PRQA S 3460 */ /* MD_Can_3460 */
# define CAN_CHANNEL_CANTYPE_FIRST
# define CAN_CHANNEL_CANTYPE_LOCAL
# define CAN_CHANNEL_CANPARA_ONLY
# define CAN_CHANNEL_CANPARA_FIRST
# define CAN_HW_CHANNEL_CANTYPE_ONLY      void    /* PRQA S 3460 */ /* MD_Can_3460 */
# define CAN_HW_CHANNEL_CANTYPE_FIRST
# define CAN_HW_CHANNEL_CANTYPE_LOCAL
# define CAN_HW_CHANNEL_CANPARA_ONLY
# define CAN_HW_CHANNEL_CANPARA_FIRST
#else
# define C_MULTIPLE_RECEIVE_CHANNEL
# define C_ENABLE_MULTICHANNEL_API
# define CAN_CHANNEL_CANTYPE_ONLY         CanChannelHandle  Controller
# define CAN_CHANNEL_CANTYPE_FIRST        CanChannelHandle  Controller,
# define CAN_CHANNEL_CANTYPE_LOCAL        CanChannelHandle  Controller; /* PRQA S 3412 */ /* MD_Can_3412 */
# define CAN_CHANNEL_CANPARA_ONLY        (CanChannelHandle) Controller
# define CAN_CHANNEL_CANPARA_FIRST       (CanChannelHandle) Controller,
#  define CAN_HW_CHANNEL_CANTYPE_ONLY     CanChannelHandle  Controller
#  define CAN_HW_CHANNEL_CANTYPE_FIRST    CanChannelHandle  Controller,
#  define CAN_HW_CHANNEL_CANTYPE_LOCAL    CanChannelHandle  Controller; /* PRQA S 3412 */ /* MD_Can_3412 */
#  define CAN_HW_CHANNEL_CANPARA_ONLY    (CanChannelHandle) Controller
#  define CAN_HW_CHANNEL_CANPARA_FIRST   (CanChannelHandle) Controller,
#endif
#if !defined(CAN_GET_STATUS)
# define CAN_GET_STATUS STD_OFF
#endif
#if (CAN_GET_STATUS == STD_ON)
# define C_ENABLE_EXTENDED_STATUS
#endif
#if !defined(CAN_INTLOCK)
# if !defined (CAN_DRIVER)
#  define CAN_DRIVER 1
# endif
# if !defined (CAN_APPL)
#  define CAN_APPL 2
# endif
# if !defined (CAN_BOTH)
#  define CAN_BOTH 3
# endif
# define CAN_INTLOCK CAN_DRIVER
#endif
#if !defined(CAN_PARTIAL_NETWORK)
# define CAN_PARTIAL_NETWORK STD_OFF
#endif
#if (CAN_PARTIAL_NETWORK == STD_ON)
# define C_ENABLE_PARTIAL_NETWORK
#endif
#if !defined(CAN_RAM_CHECK)
# define CAN_RAM_CHECK CAN_NONE
#else
# if (CAN_RAM_CHECK != CAN_NONE)
#  define C_ENABLE_CAN_RAM_CHECK
# endif
# if (CAN_RAM_CHECK == CAN_NOTIFY_MAILBOX)
#  define C_ENABLE_NOTIFY_CORRUPT_MAILBOX
# endif
#endif
#if !defined (CAN_API2) /* used for Appl_GenericConfirmation() to switch the API */
# define CAN_API2 2
#endif

#if !defined (CAN_GENERIC_PRETRANSMIT)
# define CAN_GENERIC_PRETRANSMIT STD_OFF
#endif

#if !defined (CAN_FD_SUPPORT)
# if !defined(CAN_BRS)
#  define CAN_BRS 1u
# endif
# if !defined(CAN_FULL)
#  define CAN_FULL 2u
# endif
# define CAN_FD_SUPPORT CAN_NONE
#endif

#if (CAN_FD_SUPPORT != CAN_NONE)
# define C_ENABLE_CAN_FD
# if (CAN_FD_SUPPORT == CAN_FULL)
#  define C_ENABLE_CAN_FD_FULL
# endif
#endif

#if !defined(CAN_SET_BAUDRATE_API)
# define CAN_SET_BAUDRATE_API STD_OFF
#endif

/********************** compiler abstraction *******************************/
#if defined(V_ENABLE_CBD_ABSTRACTION)
# error "V_ENABLE_CBD_ABSTRACTION already set, no ASR abstraction possible!"
#endif
#if !defined(V_ENABLE_CAN_ASR_ABSTRACTION)
# define V_ENABLE_CAN_ASR_ABSTRACTION
#endif
#if !defined(V_NULL)
# define V_NULL          NULL_PTR
#endif
#define V_NONE       /* empty used instead of extern, STATIC, volatile... */
#define CAN_AUTOMATIC    AUTOMATIC
#define CAN_TYPEDEF      TYPEDEF
#if !defined(CAN_STATIC)
# if defined(STATIC)
#  define CAN_STATIC  STATIC   /* standard by AutoSar 3.x */
# else
#  define CAN_STATIC  static   /* standard AutoSar 4.x define */
# endif
#endif
#define V_DEF_VAR(storage, vartype, memclass)                    storage VAR(vartype, CAN_##memclass)                          /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_VAR_FAR(storage, vartype)                          storage VAR(vartype, CAN_VAR_FAR)                             /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_VAR_NEAR(storage, vartype)                         storage VAR(vartype, CAN_VAR_NEAR)                            /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_VAR_TYPE(storage, vartype)                         typedef storage VAR(vartype, TYPEDEF)                         /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_P2VAR(storage, ptrtype, memclass, ptrclass)        storage P2VAR(ptrtype, CAN_##memclass, CAN_##ptrclass)        /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_P2VAR_TYPE(storage, ptrtype, ptrclass)             typedef storage P2VAR(ptrtype, TYPEDEF, CAN_##ptrclass )      /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_P2VAR_PARA(storage, ptrtype, memclass, ptrclass)   storage P2VAR(ptrtype, CAN_##memclass, CAN_##ptrclass)        /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_P2SFR_CAN(storage, ptrtype, memclass)              storage P2VAR(ptrtype, CAN_##memclass, CAN_REG_CANCELL)       /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_P2SFR_CAN_TYPE(storage, ptrtype)                   typedef storage P2VAR(ptrtype, TYPEDEF, CAN_REG_CANCELL)      /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_CONSTP2VAR(storage, ptrtype, memclass, ptrclass)   storage CONSTP2VAR(ptrtype, CAN_##memclass, CAN_##ptrclass)   /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_CONST(storage, type, memclass)                     storage CONST(type, CAN_##memclass)                           /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_CONST_TYPE(storage, type, memclass)                typedef storage CONST(type, TYPEDEF)                          /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_P2CONST(storage, ptrtype, memclass, ptrclass)      storage P2CONST(ptrtype, CAN_##memclass, CAN_##ptrclass)      /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_P2CONST_TYPE(storage, ptrtype, ptrclass)           typedef storage P2CONST(ptrtype, TYPEDEF, CAN_##ptrclass)     /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_P2CONST_PARA(storage, ptrtype, memclass, ptrclass) storage P2CONST(ptrtype, CAN_##memclass, CAN_##ptrclass)      /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_CONSTP2CONST(storage, ptrtype, memclass, ptrclass) storage CONSTP2CONST(ptrtype, CAN_##memclass, CAN_##ptrclass) /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
#define V_DEF_CONSTP2CONST_TYPE(storage, ptrtype, ptrclass)      typedef storage CONSTP2CONST(ptrtype, TYPEDEF, CAN_##ptrclass)/* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_FUNC(storage, rettype, memclass)                   storage FUNC(rettype, CAN_##memclass)                         /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_FUNC_API(storage, rettype, memclass)               storage FUNC(rettype, CAN_##memclass)                         /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_FUNC_CBK(storage, rettype, memclass)               storage FUNC(rettype, CAN_##memclass)                         /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
#define V_DEF_P2FUNC(storage, rettype, ptrclass, fctname)        storage P2FUNC(rettype, CAN_##ptrclass, fctname)              /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */

/* only use internal when not defined before */
#if !defined( vuint8 )
# define CAN_HL_NO_V_DEF
# define vuint8 uint8 /* PRQA S 3436 */ /* MD_Can_3436 */
#endif
#if !defined( vsint8 )
# define vsint8 sint8 /* PRQA S 3436 */ /* MD_Can_3436 */
#endif
#if !defined( vuint16 )
# define vuint16 uint16 /* PRQA S 3436 */ /* MD_Can_3436 */
#endif
#if !defined( vsint16 )
# define vsint16 sint16 /* PRQA S 3436 */ /* MD_Can_3436 */
#endif
#if !defined( vuint32 )
# define vuint32 uint32 /* PRQA S 3436 */ /* MD_Can_3436 */
#endif
#if !defined( vsint32 )
# define vsint32 sint32 /* PRQA S 3436 */ /* MD_Can_3436 */
#endif


#if defined( C_DRV_INTERNAL )
/* PRQA S 0850 EOF */ /* MD_Can_0850 */
#endif

/* CAN037 */
/***************************************************************************/
/* data types (need for Migration compatibility in can.h)                  */
/***************************************************************************/
V_DEF_P2VAR_TYPE(V_NONE, Std_VersionInfoType, APPL_VAR) Can_VersionInfoPtrType;
V_DEF_P2CONST_TYPE(V_NONE, Can_ConfigType, CONST_PBCFG) Can_ConfigPtrType;
V_DEF_P2CONST_TYPE(V_NONE, Can_ControllerConfigType, CONST_PBCFG) Can_ControllerConfigPtrType;
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
V_DEF_P2CONST_TYPE(V_NONE, Can_ControllerBaudrateConfigType, APPL_VAR) Can_ControllerBaudrateConfigPtrType;
#endif
V_DEF_P2CONST_TYPE(V_NONE, Can_PduType, APPL_VAR) Can_PduInfoPtrType;
V_DEF_P2VAR_TYPE(V_NONE, Can_PduType, APPL_VAR)   Can_PduInfoPtrType_var;
V_DEF_P2CONST_TYPE(V_NONE, uint8, RX_TX_DATA)     Can_DataPtrType;

/* data types for driver function parameters */
/* the types of CanInitHandle, CanChannelHandle and CanObjectHandle depends
   on the compiler and controller - what generates effective code */
typedef vuint16           CanInitHandle;
typedef vuint16           CanChannelHandle;
/* CanObjectHandle has to be unsigned! */
typedef vuint16           CanObjectHandle;

typedef vuint16           CanTransmitHandle;
typedef vuint16           CanReceiveHandle;

/* define datatype of local signed variables for message handles */


 /* ptr to msgObj & data on chip used in precopy function */
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipDataPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint8)  CanChipMsgPtr;
V_DEF_P2SFR_CAN_TYPE(volatile, vuint32) CanChipMsgPtrType;

/* up to 5 tables can be defined for the transmission ID. The type and how 
   many tables are needed depends on the CPU bus type and on the ID registers 
   of the CAN controller. E.g. a CPU with a 16-Bit bus and 2 byte ID registers 
   for standard ID needs 1 table and tCanRxId0 of type vuint16. The same CPU
   with 5 byte ID registers for extended ID needs in this case 3 tables and
   tCanRxId0 = vuint16, tCanRxId1 = vuint16 and tCanRxId2 = vuint16. */
typedef vuint16         tCanTxId0;
#if defined( C_ENABLE_EXTENDED_ID )
typedef vuint16         tCanTxId1;
#endif

/* unused by this driver: 
typedef vuint8          tCanTxId2;
typedef vuint8          tCanTxId3;
typedef vuint8          tCanTxId4;
*/

/* type of variable for ID type kCanIdTypeExt or kCanIdTypeStd will be assigned to 
   a variable of this type */
typedef vuint16          tCanIdType;

/* up to 3 tables can be defined for the reception ID. The type and how many
   tables are needed depends on the CPU bus type and on the ID registers of
   the CAN controller. E.g. a CPU with a 16-Bit bus and 2 byte ID registers 
   for standard ID needs 1 table and tCanRxId0 of type vuint16. The same CPU
   with 5 byte ID registers for extended ID needs in this case 3 tables and 
   tCanRxId0 = vuint16, tCanRxId1 = vuint16 and tCanRxId2 = vuint16. */

typedef vuint16          tCanRxId0;

#if defined( C_ENABLE_EXTENDED_ID )
typedef vuint16          tCanRxId1;
#endif

/* unused by this driver: 
typedef vuint16          tCanRxId2;
typedef vuint16          tCanRxId3;
typedef vuint16          tCanRxId4;
*/

/* type of the variable, in which the old status of the interrupt flag or
   level is stored */
typedef vuint16         tCanHLIntOld;


/* CAN043 */
/***************************************************************************/
/* function prototypes / API                                               */
/***************************************************************************/
#define CAN_START_SEC_CODE  /*---------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (CAN_VERSION_INFO_API == STD_ON) /* BR:007 */
V_DEF_FUNC(V_NONE, void, CODE) Can_GetVersionInfo( Can_VersionInfoPtrType VersionInfo );
#endif
V_DEF_FUNC(V_NONE, void, CODE) Can_Init( Can_ConfigPtrType ConfigPtr );
#if (CAN_MICROSAR_VERSION == CAN_MSR40)
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerBaudrateConfigPtrType Config );
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR403)
# if ((CAN_CHANGE_BAUDRATE_SUPPORT == STD_ON) || (CAN_SET_BAUDRATE_API == STD_OFF))
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_ChangeBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate );
# endif
# if (CAN_CHANGE_BAUDRATE_SUPPORT == STD_ON)
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckBaudrate( uint8 Controller, V_DEF_CONST(V_NONE, uint16, APPL_CONST) Baudrate );
# endif
# if (CAN_SET_BAUDRATE_API == STD_ON)
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_SetBaudrate( uint8 Controller, uint16 BaudRateConfigID );
# endif
#endif
#if (CAN_MICROSAR_VERSION == CAN_MSR30)
V_DEF_FUNC(V_NONE, void, CODE) Can_InitController( uint8 Controller, Can_ControllerConfigPtrType ControllerConfigPtr );
#endif

V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_SetControllerMode( uint8 Controller, Can_StateTransitionType Transition );
V_DEF_FUNC(V_NONE, Can_ReturnType, CODE) Can_Write( Can_HwHandleType Hth, Can_PduInfoPtrType PduInfo );

/* function for CAN interrupt access */
V_DEF_FUNC(V_NONE, void, CODE) Can_DisableControllerInterrupts( uint8 Controller );
V_DEF_FUNC(V_NONE, void, CODE) Can_EnableControllerInterrupts( uint8 Controller );

/* polling functions (always available for non polled systems also) */
#if (CAN_MICROSAR_VERSION == CAN_MSR30)
/* MSR4x: prototype by SchM-header */
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Write( void );
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_BusOff( void );
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Read( void );
V_DEF_FUNC(V_NONE, void, CODE) Can_MainFunction_Wakeup( void );
#endif

#define Can_Cbk_CheckWakeup Can_CheckWakeup /* compatibility to AutoSar3 */
V_DEF_FUNC(V_NONE, Std_ReturnType, CODE) Can_CheckWakeup( uint8 Controller );

/* special function (no AUTOSAR feature) */
V_DEF_FUNC(V_NONE, void, CODE) Can_InitMemory( void );
V_DEF_FUNC(V_NONE, void, CODE) Can_CancelTx( Can_HwHandleType Hth, PduIdType PduId );
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffStart( uint8 Controller );
V_DEF_FUNC(V_NONE, void, CODE) Can_ResetBusOffEnd( uint8 Controller );
#if (CAN_MICROSAR_VERSION == CAN_MSR30)
V_DEF_FUNC(V_NONE, void, CODE) Can_InitStruct( uint8 Controller, uint8 Index );
#endif
#if (CAN_GET_STATUS == STD_ON)
V_DEF_FUNC(V_NONE, uint8, CODE) Can_GetStatus( uint8 Controller );
#endif

/* ISR prototypes (see can_irq.c) */

/* Possibility to disable the prototypes of interrupt service routines in the driver configuration header file.  */
# if !(defined( C_ENABLE_ISR_PROTOTYPE) || defined( C_DISABLE_ISR_PROTOTYPE ))
#  define C_ENABLE_ISR_PROTOTYPE
# endif


#if defined (C_ENABLE_ISR_PROTOTYPE)
# if defined(C_ENABLE_OSEK_OS)&&\
     defined(C_ENABLE_OSEK_OS_INTCAT2)
/* ISR prototypes mus be provided by OSEK header file */
# else
#  if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
       (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
        !defined( C_ENABLE_TX_POLLING )        || \
        defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
        !defined( C_ENABLE_ERROR_POLLING )     ||\
        !defined( C_ENABLE_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration*/
#   if defined( kCanPhysToLogChannelIndex_0 )
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_0(void);
#   endif
#   if defined( kCanPhysToLogChannelIndex_1 )
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_1(void);
#   endif
#   if defined( kCanPhysToLogChannelIndex_2 )
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_2(void);
#   endif
#  endif /* no pure polling configuration */
# endif
#endif /* if defined (C_ENABLE_ISR_PROTOTYPE) */

# if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
      (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
       !defined( C_ENABLE_TX_POLLING )        || \
       defined( C_ENABLE_INDIVIDUAL_POLLING ) || \
       !defined( C_ENABLE_ERROR_POLLING )     ||\
       !defined( C_ENABLE_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration*/
/* CODE CATEGORY 1 START */
V_DEF_FUNC(V_NONE, void, CODE) Can_CellIsr( CAN_HW_CHANNEL_CANTYPE_ONLY );
/* CODE CATEGORY 1 END */
# endif

#define CAN_STOP_SEC_CODE  /*------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CAN_START_SEC_CODE_APPL  /*----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (CAN_GENERIC_PRECOPY == STD_ON)
V_DEF_FUNC(extern, Can_ReturnType, APPL_CODE) Appl_GenericPrecopy( uint8 Controller, Can_IdType ID, uint8 DLC, Can_DataPtrType DataPtr );
#endif
#if (CAN_GENERIC_CONFIRMATION == STD_ON)
V_DEF_FUNC(extern, Can_ReturnType, APPL_CODE) Appl_GenericConfirmation( PduIdType PduId );
#endif
#if (CAN_GENERIC_CONFIRMATION == CAN_API2)
V_DEF_FUNC(extern, Can_ReturnType, APPL_CODE) Appl_GenericConfirmation( uint8 Controller, Can_PduInfoPtrType DataPtr );
#endif
#if (CAN_GENERIC_PRETRANSMIT == STD_ON)
V_DEF_FUNC(extern, void, APPL_CODE) Appl_GenericPreTransmit( uint8 Controller, Can_PduInfoPtrType_var DataPtr );
#endif
#if (CAN_HARDWARE_CANCELLATION == STD_ON) || (((CAN_MICROSAR_VERSION == CAN_MSR40) || (CAN_MICROSAR_VERSION == CAN_MSR403)) ) /* always used for sync mode */
# if (CAN_HW_LOOP_SUPPORT_API == STD_ON)
V_DEF_FUNC(V_NONE, void, APPL_CODE) ApplCanTimerStart( CAN_CHANNEL_CANTYPE_FIRST uint8 source );
V_DEF_FUNC(V_NONE, Can_ReturnType, APPL_CODE) ApplCanTimerLoop( CAN_CHANNEL_CANTYPE_FIRST uint8 source );
V_DEF_FUNC(V_NONE, void, APPL_CODE) ApplCanTimerEnd( CAN_CHANNEL_CANTYPE_FIRST uint8 source );
# endif
#endif
#if (CAN_INTLOCK != CAN_DRIVER)
V_DEF_FUNC(extern, void, APPL_CODE) ApplCanInterruptDisable( uint8 Controller );
V_DEF_FUNC(extern, void, APPL_CODE) ApplCanInterruptRestore( uint8 Controller );
#endif

#if (CAN_OVERRUN_NOTIFICATION == CAN_APPL)
V_DEF_FUNC(extern, void, APPL_CODE) Appl_CanOverrun ( uint8 Controller );
V_DEF_FUNC(extern, void, APPL_CODE) Appl_CanFullCanOverrun ( uint8 Controller );
#endif

#if defined( C_ENABLE_CAN_RAM_CHECK )
# if defined( C_ENABLE_NOTIFY_CORRUPT_MAILBOX )
V_DEF_FUNC(extern, void, APPL_CODE) Appl_CanCorruptMailbox(uint8 Controller, Can_HwHandleType hwObjHandle);
# endif
V_DEF_FUNC(extern, uint8, APPL_CODE) Appl_CanRamCheckFailed(uint8 Controller);
#endif

/* CAN238 */
/* CODE CATEGORY 1 START*/
#if defined( C_ENABLE_SLEEP_WAKEUP )
V_DEF_FUNC_CBK(V_NONE, vuint8, APPL_CODE) ApplCanGoToSleepModeRequest(CAN_CHANNEL_CANTYPE_ONLY);
V_DEF_FUNC_CBK(V_NONE, vuint8, APPL_CODE) ApplCanWakeUpFromSleepModeRequest(CAN_CHANNEL_CANTYPE_ONLY);
#endif
/* CODE CATEGORY 1 END*/

#define CAN_STOP_SEC_CODE_APPL  /*-----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if !defined( C_DRV_INTERNAL ) && defined( CAN_HL_NO_V_DEF )
/* only use internal when not defined before */
# undef vuint8
# undef vsint8
# undef vuint16
# undef vsint16
# undef vuint32
# undef vsint32
#endif

/* PRQA  L:QAC_Can_0828 */
/* PRQA  L:QAC_Can_0850 */

#endif /* end file */
/*  STOPSINGLE_OF_MULTIPLE_COMMENT  */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */


/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 595 */


/************   Organi, Version 3.9.1 Vector-Informatik GmbH  ************/
