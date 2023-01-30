/*  *****   STARTSINGLE_OF_MULTIPLE_COMMENT    *****  */




/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  Copyright (c) 2008 - 2013 by Vector Informatik GmbH.                                            All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
         File:  CanSM_BswM.h
    Component:  CAN State Manager
       Module:  -
    Generator:  -

  Description:  Public header of the CAN State Manager AUTOSAR Release 3.0
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Mark A. Fingerle              mfi           Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  01.16.00  2011-01-13  mfi     ESCAN00046656 Call Appl_CanSM_BusOffEnd() if a BusOff recovery is interrupted
                                ESCAN00047400 change shutdown sequence for Partial Network
                                ESCAN00046783 Support Multiple Identity Configuration
                                ESCAN00047494 Adapt CanSM for usage with IdentityManagerConfig
                                ESCAN00047436 BswM callout BswM_CanSM_CurrentState
                                ESCAN00044505 The application call back function declaration is surround by the same MemMap.h section as CanSM code
                                ESCAN00047985 No CAN communication possible, caused by bus-off in SILENT communication
                                ESCAN00048379 Definition CANSM_PRE_COMPILE used before it is set - Build Lib Check not usable
  01.16.01  2011-05-05  mfi     ESCAN00044505 The application call back function declaration is surround by the same MemMap.h section as CanSM code
                                ESCAN00050250 Extend Bus Off recovery handling, additional ModeIndications during BusOff recovery
  01.17.00  2011-06-05  mfi     ESCAN00050284 Add partial network functionality according to the CanSM SWS (AUTOSAR 3.2.1)
                                ESCAN00051096 Call SetControllerMode (or TransceiverMode) during startup only if necessary (during startup)
                                ESCAN00051239 Add Support for BorTxConfirmationPolling (AUTOSAR 3.2.1)
                                ESCAN00050674 MISRA deviation: MISRA-C:2004 Rule 13.7 3355
                                ESCAN00052195 Add new API to set Channel in passive mode
  01.17.01  2011-08-18  mfi     ESCAN00052900 CanSM reacts on TrcvModeIndication caused by WU interrupt (WU may fail)
  01.17.02  2011-08-22  mfi     ESCAN00052924 Wrong Version defines
  01.18.00  2011-11-22  mfi     ESCAN00053607 Remove non-SchM code for critical section handling (AR3-2069)
                                ESCAN00054366 Add support of CanSm_TxTimeoutException (AR3-2024)
                                ESCAN00054367 Add support of 2 new PDU modes for partial network (AR3-2024)
                                ESCAN00055111 No CAN communication is possible because Trcv Mode is STANDBY instead NORMAL
                                ESCAN00052902 CanSM gets wrong configuration data during initialization (SEC_PBCFG_ROOT)
                                ESCAN00055904 Det_ReportError() not called (E_PARAM_TRANSCEIVER or E_INVALID_NETWORK_HANDLE)
                                ESCAN00055942 Bus stays online after passive mode request (CanSM_SetEcuPassive or CanSM_SetCanChannelPassive)
                                ESCAN00055985 Dem Error CANSM_E_MODE_CHANGE triggered to early (CanSMNwSmMaxRepetitions)
  01.18.01  2012-03-22  mfi     ESCAN00056011 Dem Error CANSM_E_MODE_CHANGE is triggered in each main function cycle
  01.18.02  2012-04-22  mfi     ESCAN00058392 CAN communication stays awake even PartialNetwork not requested
  01.19.00  2012-08-22  mfi     ESCAN00059927 Implement CAN bus-off behavior according to AUTOSAR 3.2.2 (AR3-2447)
                                ESCAN00061218 PduMode wakeup filter, Update Partial Network Handling according ASR3.2.2 (AR3-2398)
  01.19.01  2012-10-22  mfi     ESCAN00062521 Remove compiler abstraction by typedef V A R
                                ESCAN00062564 Partial Networking Wakeup Tx Pdu Filter doesn't work (CANSM_PARTIAL_NETWORK_WAKEUP_FILTER)
  01.19.02  2013-01-03  mfi     ESCAN00063651 CAN communication not started if the ECU is in power off and CAN wakeup validation is used
                                ESCAN00063734 CAN communication not started, because CAN wakeup validation failed
                                ESCAN00063730 Add API to start and stop the CAN HW in case of a wakeup validation
                                ESCAN00063996 Correct spelling of service ID of CanSM_SetCanChannelPassive()
                                ESCAN00064035 GetCurrentComMode() delivers wrong mode during running bus-off recovery
  01.20.00  2013-03-23  mfi     ESCAN00065276 Add possibility to deactivate PN functionality at runtime
                                ESCAN00064899 ECU does not shut down properly when a CAN channel is not connected to the bus (CanSM_TxTimeoutException in Silent)
                                ESCAN00067201 Implement AMD timemeasurement support
  01.21.00  2013-06-03  mfi     ESCAN00067834 CanSM_GetCurrentComMode() delivers wrong mode after shutdown during running bus-off recovery
                                ESCAN00067518 ECU does not enter sleep/stop mode or cannot be woken up again
**********************************************************************************************************************/

#ifndef CANSM_BSWM_H

# define CANSM_BSWM_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

/**********************************************************************************************************************
* Version
**********************************************************************************************************************/
/* AUTOSAR CAN State Management version */
/* ##V_CFG_MANAGEMENT ##CQProject : Ccl_AsrSmCan CQComponent : Implementation */
# define CCL_ASRSMCAN_BSWM_HEADER_VERSION                             0x0121u   /* BCD coded version number */
# define CCL_ASRSMCAN_BSWM_HEADER_RELEASE_VERSION                     0x00u    /* BCD coded release version number  */


/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
# include "Platform_Types.h"
# include "Compiler_Cfg.h"

# define CANSM_BSWM_NO_COMMUNICATION       0u
# define CANSM_BSWM_SILENT_COMMUNICATION   1u
# define CANSM_BSWM_FULL_COMMUNICATION     2u
# define CANSM_BSWM_BUS_OFF                3u

typedef uint8 CanSM_BswMCurrentStateType;


/*******************************************************************************
* Organi check
*******************************************************************************/


#endif /* end if not defined ( CANSM_BSWM_H ) */
/**********************************************************************************************************************
  END OF FILE: CanSM_BswM.h
**********************************************************************************************************************/
/*  *****   STOPSINGLE_OF_MULTIPLE_COMMENT    *****  */

