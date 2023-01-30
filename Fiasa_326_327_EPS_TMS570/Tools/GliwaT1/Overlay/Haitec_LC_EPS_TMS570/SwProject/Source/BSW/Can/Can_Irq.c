/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 544 */

/* STARTSINGLE_OF_MULTIPLE */
/*****************************************************************************
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| Bir          Holger Birke              Vector Informatik GmbH
| Ces          Senol Cendere             Vector Informatik GmbH
|-----------------------------------------------------------------------------
|               IRQ    R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver      Author    Description
| ----------  -------  --------- ---------------------------------------------
| 2007-07-27  0.01.00  Bir       - initial version
| 2007-08-10  0.02.00  Ces       - added OSEK type specific include 
|                                - added interrupt category selection                             
| 2007-08-13  1.00.00  Bir       - missing #endif
|                                - move osek-switches out of irq.c
| 2008-04-16  1.01.00  Bir       - ESCAN00026087: Case sensitive naming for all File names (and includes)
| 2009-04-20  1.02.00  Bir       - ESCAN00034119: Add memory abstraction
| 2010-01-19  1.02.01  Bir       - ESCAN00040234: remove v_cfg.h include (already done in can_cfg.h)
| 2010-11-23  1.03.00  Bir       - ESCAN00043999: Support usage without v_def.h
| 2011-11-14  1.03.01  Bir       - ESCAN00053270: Add Misra comments
| 2011-06-21  1.03.02  Bir       - ESCAN00056004: Add Code Traceability to AutoSar SWS
| 2012-10-31  1.03.03  Bir       - ESCAN00062679: Add source defines according to MICROSAR template source file
|***************************************************************************/
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
| Copyright (c) 1996-2012 by Vector Informatik GmbH.       All rights reserved.
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
|************************************************************************* */

/***************************************************************************/
/* Include files                                                           */
/***************************************************************************/
#define C_DRV_INTERNAL
#define CAN_IRQ_SOURCE     /* testability */

/* PRQA S 0850 EOF */ /* MD_Can_0850 */
/* PRQA S 0828 EOF */ /* MD_Can_0828 */

#include "Can.h"
#if defined(V_OSTYPE_OSEK)
# include "osek.h"
#endif
/* CAN034 */
#if defined(V_OSTYPE_AUTOSAR)
# include "Os.h"
#endif

#include "Metrics.h"

#ifndef T1_ENABLE
#error "This version of Can_Irq.c is only intended for a metrics build."
#endif


/***************************************************************************/
/* Version Check  against included API                                     */
/***************************************************************************/
#if (DRVCAN_APIASR_VERSION             != 0x0402u)
# error "Source and Header file are inconsistent!"
#endif
#if (DRVCAN_APIASR_RELEASE_VERSION     != 0x00u)
# error "Source and Header file are inconsistent!"
#endif

#if defined(C_ENABLE_MULTI_ECU_CONFIG)
V_DEF_VAR(extern, uint16, VAR_NOINIT) canActiveIdentityMsk; /* PRQA S 3447,3210 */ /* MD_Can_Asr_3447 */
V_DEF_VAR(extern, uint8, VAR_NOINIT)  canActiveIdentityLog; /* PRQA S 3447,3210 */ /* MD_Can_Asr_3447 */
#endif

#if defined V_ACTIVE_IDENTITY_MSK
# undef V_ACTIVE_IDENTITY_MSK  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
#define V_ACTIVE_IDENTITY_MSK                canActiveIdentityMsk
#if defined V_ACTIVE_IDENTITY_LOG
# undef V_ACTIVE_IDENTITY_LOG  /* this define from v_cfg.h is replaced and no more used (but header may included by other module) */ /* PRQA S 0841 */ /* MD_Can_0841 */
#endif
#define V_ACTIVE_IDENTITY_LOG                canActiveIdentityLog

/***************************************************************************/
/* Interrupt Service Routine                                               */
/***************************************************************************/
#define CAN_START_SEC_CODE  /*-----------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* CAN033 (P), CAN035, CAN420 */
#if ((defined( C_ENABLE_RX_BASICCAN_OBJECTS ) && !defined( C_ENABLE_RX_BASICCAN_POLLING )) || \
     (defined( C_ENABLE_RX_FULLCAN_OBJECTS )  && !defined( C_ENABLE_RX_FULLCAN_POLLING  )) || \
      !defined( C_ENABLE_TX_POLLING )        || \
      !defined( C_ENABLE_ERROR_POLLING )     ||\
      !defined( C_ENABLE_WAKEUP_POLLING ))        /* ISR necessary; no pure polling configuration*/
/* **************************************************************************
| NAME:             CanIsr_0
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt stucture
|
|  Attention:  <Name> has to be repleased with the name of the ISR. 
|              Naming conventions: with Name = "", "Rx", "Tx", "RxTx", "Wakeup", "Status" 
|  The name of the ISR will always have a channel index at the end. Even in single channel
|  systems.
************************************************************************** */
/* CODE CATEGORY 1 START */
# if defined( kCanPhysToLogChannelIndex_0 )
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_0 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
       defined (osdIsrCanIsr_0Cat)
#    if (osdIsrCanIsr_0Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_0( void )
#  endif /* C_ENABLE_OSEK_OS */
{
  Metrics_TaskStart(T1_CanIsr_0_ID);

#  if defined( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CellIsr(CanPhysToLogChannel[V_ACTIVE_IDENTITY_LOG][0]);           /* call Interrupthandling with identity dependend logical channel */ /* SBSW_CAN_LL001 */
#  else
#   if defined( C_SINGLE_RECEIVE_CHANNEL )
  Can_CellIsr();
#   else
  Can_CellIsr(kCanPhysToLogChannelIndex_0);            /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
#   endif
#  endif

  Metrics_TaskEnd(T1_CanIsr_0_ID);
} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_0) */
/* CODE CATEGORY 1 END */
/* **************************************************************************
| NAME:             CanIsr_1
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt stucture
|
|  Attention:  <Name> has to be repleased with the name of the ISR. 
|              Naming conventions: with Name = "", "Rx", "Tx", "RxTx", "Wakeup", "Status" 
|  The name of the ISR will always have a channel index at the end. Even in single channel
|  systems.
************************************************************************** */
/* CODE CATEGORY 1 START */
# if defined( kCanPhysToLogChannelIndex_1 )
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_1 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
       defined (osdIsrCanIsr_1Cat)
#    if (osdIsrCanIsr_1Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_1( void )
#  endif /* C_ENABLE_OSEK_OS */
{

#  if defined( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CellIsr(CanPhysToLogChannel[V_ACTIVE_IDENTITY_LOG][1]);           /* call Interrupthandling with identity dependend logical channel */ /* SBSW_CAN_LL001 */
#  else
#   if defined( C_SINGLE_RECEIVE_CHANNEL )
  Can_CellIsr();
#   else
  Can_CellIsr(kCanPhysToLogChannelIndex_1);            /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
#   endif
#  endif

} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_1) */
/* CODE CATEGORY 1 END */
/* **************************************************************************
| NAME:             CanIsr_2
| CALLED BY:        HLL, Asr: Interrupt
| PRECONDITIONS:
| INPUT PARAMETERS: none
| RETURN VALUES:    none
| DESCRIPTION:      Interrupt service functions according to the CAN controller
|                   interrupt stucture
|
|  Attention:  <Name> has to be repleased with the name of the ISR. 
|              Naming conventions: with Name = "", "Rx", "Tx", "RxTx", "Wakeup", "Status" 
|  The name of the ISR will always have a channel index at the end. Even in single channel
|  systems.
************************************************************************** */
/* CODE CATEGORY 1 START */
# if defined( kCanPhysToLogChannelIndex_2 )
#  if defined( C_ENABLE_OSEK_OS ) && \
      defined( C_ENABLE_OSEK_OS_INTCAT2 )
#   if defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 2)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
ISR( CanIsr_2 )
#  else
#   if defined( C_ENABLE_OSEK_OS ) && \
       defined (osdIsrCanIsr_2Cat)
#    if (osdIsrCanIsr_2Cat != 1)
#     error "inconsistent configuration of Osek-OS interrupt categorie between CANgen/GENy and OIL-configurator (CanIsr)"
#    endif
#   endif
V_DEF_FUNC(V_NONE, void, CODE) CanIsr_2( void )
#  endif /* C_ENABLE_OSEK_OS */
{

#  if defined( C_ENABLE_MULTI_ECU_CONFIG )
  Can_CellIsr(CanPhysToLogChannel[V_ACTIVE_IDENTITY_LOG][2]);           /* call Interrupthandling with identity dependend logical channel */ /* SBSW_CAN_LL001 */
#  else
#   if defined( C_SINGLE_RECEIVE_CHANNEL )
  Can_CellIsr();
#   else
  Can_CellIsr(kCanPhysToLogChannelIndex_2);            /* call Interrupthandling with logical channel */ /* SBSW_CAN_LL001 */
#   endif
#  endif

} /* END OF CanISR */
# endif /* (kCanPhysToLogChannelIndex_2) */
/* CODE CATEGORY 1 END */

#endif  /* Not a pure polling configuration */


#define CAN_STOP_SEC_CODE  /*------------------------------------------*/
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 544 */

/* Kernbauer Version: 1.16 Konfiguration: DrvCAN Erzeugungsgangnummer: 544 */

