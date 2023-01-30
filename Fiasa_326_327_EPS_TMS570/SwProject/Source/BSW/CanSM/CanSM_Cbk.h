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
         File:  CanSM_Cbk.h
    Component:  CAN State Manager
       Module:  -
    Generator:  -

  Description:  Call back header of the CAN State Manager AUTOSAR Release 3.0
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
  00.01.00  2007-11-05  mfi     -             Initial version
  01.00.00  2008-01-23  mfi     -             ASR 3.0 release version of SWS, CanIf still on ASR 2.1
                                ESCAN00025949 The CanSM isn't affected. The CanSM handles the DEM already in the Lcfg.c (No access on "DEM-events" via DEM created and exported constant values)
  01.01.00  2008-02-04  mfi     ESCAN00024939 New Transition T00 (UNINIT to FULL),
                                ESCAN00024941 Set Transceiver to SILENT only if Controller is in SLEEP
  01.02.00  2008-02-25  mfi     ESCAN00024924 CAN not performs bus-off recovery
  01.03.00  2008-02-28  mfi     ESCAN00024985 Deadline monitoring not active in FULL communication and may be active in NO communication. Switched DL on in T00 and T02. Switched DL off in T03.
  01.04.00  2008-03-03  mfi     ESCAN00025095 Memory Mapping and Compiler Abstraction added
                                ESCAN00025096 Check if the configuration contains same NW index multiple times.
                                ESCAN00024943 The CanSM passes wrong parameter to the ComM. The parameter list in the function calls are switched.
                                ESCAN00025099 Activate Transceiver before Controller
                                ESCAN00025100 Version defines and version checks added/modified
                                ESCAN00025101 Switched API ComM_BusSM_ModeIndication and header file ComM_BusSM.h
                                ESCAN00025111 Adapt CanSM to ASR 3.0 CanIf, CanSM is still able to handle CanIf 2.1 too. API becomes chosen automatically
                                ESCAN00025138 API prototype GetVersionInfo in wrong header file
                                ESCAN00025139 First bus-off recovery time of level 2 may be to short
  01.05.00  2008-03-31  mfi     ESCAN00025653 CA _STATIC_ substituted by ASR 3.0 STATIC; doubled semicolon removed
                                ESCAN00025677 Include all CanSM headers, to check the version number
                                ESCAN00026039 Compiler error "Unrecognized token ';'" issued (... CanSm_Config_Ptr = NULL_PTR;;)
  01.06.00  2008-04-04  mfi     ESCAN00025892 Simplify the set controller mode algorithm of the CanSM
                                ESCAN00025893 Implement a check if E_OK has the value 0
                                ESCAN00025894 Reduce complexity of bus-off value handling
                                ESCAN00025895 Speedup evaluation of the conditions in the bus-off state machine
                                ESCAN00025896 Modified the return value of CanSM_RequestComMode
                                ESCAN00026000 Modify compiler abstraction according Newsletter
                                ESCAN00026001 Extend error handling to the case a transition fails and the mode request changes before recovering of the transition.
                                ESCAN00026002 Add an error counter and a DEM event triggered by the counter
                                ESCAN00026003 MetaStates of BOR SM shifted in NW SM
                                ESCAN00026110 Channel specific transceiver handling
                                ESCAN00026111 Switched form SW number to ASR number to check the version of the CanIf
                                ESCAN00026112 CanSM has defined wrong ASR version number
                                ESCAN00026122 The values of the pre-compile switch CANSM_BOR_DISABLE_RX_DL_MONITORING are interchanged
                                ESCAN00026176 Extension for MSR3.0 LinkTime checks
                                ESCAN00026347 Remove Compiler warning "condition is always true" in CanSM_Init
                                ESCAN00026269 Rename files and #include statements according coding styles
  01.07.00  2008-05-26  mfi     ESCAN00026502 Extension for MSR3.0 generator version checks
                                ESCAN00027533 CanSM don't report a Dem error if error counter exceeded
                                ESCAN00027592 Remove unnecessary if statement
  01.07.01  2008-06-04  mfi     ESCAN00028140 Extension for MSR3.0 generator version checks, changes added (typecast, stop init)
                                ESCAN00028247 The values of the preprocessor switch CanSMBorDisableRxDlMonitoring are switched.
  01.08.00  2008-07-24  mfi     ESCAN00028853 General improvements (pointer to the current channel data; defines instead of explicit value;  remove unused variable)
                                ESCAN00028328 Remove compatibility to CanIf ASR 2.1
                                ESCAN00027977 Resource and Runtime optimization at DET calls
                                ESCAN00028851 CanSM_GetCurrentComMode returns illegal E_NOT_OK
                                ESCAN00029339 Pointer for ComM_BusSM_ModeIndication as parameter
                                ESCAN00029365 Configuration switch "Rx deadline monitoring" changeable at linktime too
                                ESCAN00029501 Boolean type CanSm_IsInitialized changed to uint8
                                ESCAN00028889 The CAN controller not started in second level of the bus-off recovery ==> T07, T13, T12 are similar and joined ==> BOR SM modified
                                ESCAN00028814 Add brackets that CANSM_LeaveCritical and CANSM_EnterCritical look like functions
                                ESCAN00028323 Remove the redundant check CANSM_BOR_CHECK_INIT in Transition T09
                                ESCAN00028885 Resource and Runtime optimization at transceiver calls
  01.09.00  2008-09-23  mfi     ESCAN00030248 Use UpperCamelCase notation for the configuration parameter
                                ESCAN00030000 PreCompile and Linktime CRC check [BR]
                                ESCAN00029792 Resource and Runtime optimization at controller calls
                                ESCAN00030492 CAN bus specific bus-off configuration parameter
                                ESCAN00030619 Add support for the ECU passive mode (CanSM_SetEcuPassive) [022]
                                ESCAN00030656 Remove unused defines
                                ESCAN00030657 Add ASR short name prefix to defines
                                ESCAN00030658 Correct the pointer and memory class in the compiler abstraction macros
                                ESCAN00030659 Remove the init value of UNINIT variable
                                ESCAN00030663 Add compiler abstraction for function local pointers to data defined in the link or post build files
  01.10.00  2008-11-13  mfi     ESCAN00031381 CanSM includes wrong header ("Platform_Types.h" instead Std_Types.h)
                                ESCAN00031377 CanSM uses wrong compiler abstraction
                                ESCAN00031378 Error detection related code not encapsulated in pre-processor switches
                                ESCAN00031582 Deadline Monitoring not started
                                ESCAN00031970 Missing function declaration because of unknown define value
  01.11.00  2009-02-13  mfi     ESCAN00033112 Conditional skip transceiver mode set during initialization [023]
                                ESCAN00033173 Compiler abstraction and memory mapping for local variables are missing.
  01.11.01  2009-03-23  mfi     ESCAN00033501 Compiler Warnings CanSM_TransceiverMode, "CanSM_TransceiverMode" was declared but never referenced
                                ESCAN00034044 Compiler Warning "pointless comparison of unsigned integer with zero"
                                ESCAN00034070 Move CanSM passive mode API into CanSM.h file
                                ESCAN00034158 Wrong memory mapping for pointers to CanSM_LocalClusterDataType variables
  01.12.00  2009-05-27  mfi     ESCAN00034660 The type CanSM_NetworkModeStateType and CanSM_BusOffRecoveryStateType is not implemented correct
                                ESCAN00035004 CAN bus does not react on external wakeup interrupts ==> No repetition if set Trcv mode fail in the transition T03 OR T01
                                ESCAN00035856 CanSM increases the repetition error counter twice if transceiver produces a negative return value in T02
                                ESCAN00036045 Inform the application about a present bus-off [010]
                                ESCAN00036438 Misra violation Rule 5.6; Name Spaces of Identifiers
                                ESCAN00036095 Pre-processor checks for building the library
  01.12.01  2009-09-09  mfi     ESCAN00037693 Dcm throws Det error during initialization of the CanSM
  01.12.02  2009-10-23  mfi     ESCAN00038504 Wrong compiler abstraction
  01.12.03  2010-03-03  mfi     ESCAN00041368 Interrupt locks take very long during state changes
  01.13.00  2010-04-23  mfi     ESCAN00041156 Naming of CanSM functions and macros is inconsistent
  01.14.00  2010-07-13  mfi     ESCAN00043552 Submitted Add support for XCP shutdown
  01.15.00  2010-10-03  mfi     ESCAN00045704 Disable DeadlineMonitoring in state CANSM_SILENT_COMMUNICATION
                                ESCAN00045815 CanSM tries to call missing functions;  encapsulate DM in CANSM_BOR_DISABLE_RX_DL_MONITORING
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

#ifndef CANSM_CBK_H

# define CANSM_CBK_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/

# include "ComStack_Types.h"   /* NetworkHandleType */
# include "CanIf_Cfg.h"     /* CanIf_TransceiverModeType */
# include "Std_Types.h"      /* uint8 */


/**********************************************************************************************************************
* Version
**********************************************************************************************************************/
/* AUTOSAR CAN State Management version */
/* ##V_CFG_MANAGEMENT ##CQProject : Ccl_AsrSmCan CQComponent : Implementation */
# define CCL_ASRSMCAN_CALLBACK_HEADER_VERSION                             0x0121u   /* BCD coded version number */
# define CCL_ASRSMCAN_CALLBACK_HEADER_RELEASE_VERSION                     0x00u    /* BCD coded release version number  */


/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
  Callback Functions
**********************************************************************************************************************/

# define CANSM_START_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*********************************************************************************************************************
  FUNCTION: CanSM_ControllerBusOff
----------------------------------------------------------------------------------------------------------------------
  API     Type                        Name                        Description
----------------------------------------------------------------------------------------------------------------------
   Input: CanSm_ControllerIdType      CanSm_ControllerId
  Output: CanSm_BusOffEventType       CanSm_BusOffEventOccurred   modifies the actual system state
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: CanIf

  This API function is used to notify the CanSM about a bus-off event
*********************************************************************************************************************/
FUNC(void, CANSM_CODE) CanSM_ControllerBusOff( uint8 CanSm_ControllerId );


/***********************************************************************************************************************
*  CanSM_TransceiverModeIndication
**********************************************************************************************************************/
/*! \brief     This API function is used to notify the CanSM about the change of the transceiver mode
*  \param[in]  CanSM_TransceiverId     CAN transceiver, whose mode has changed
*  \param[in]  CanSM_TransceiverMode   Current CAN transceiver mode
*  \pre        Input parameter must be valid.
*  \context    Function could be called from interrupt level or from task level
*  \note
**********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_TransceiverModeIndication( uint8 CanSM_TransceiverId, CanIf_TransceiverModeType CanSM_TransceiverMode );


/***********************************************************************************************************************
*  CanSM_ClearTrcvWufFlagIndication
**********************************************************************************************************************/
/*! \brief     This callback function indicates the CanIf_ClearTrcvWufFlag API process end
*  \param[in]  CanSM_Transceiver     Requested Transceiver
*  \pre        Input parameter must be valid.
*  \context    Function could be called from interrupt level or from task level
*  \note
**********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_ClearTrcvWufFlagIndication  ( uint8 CanSM_TransceiverId );


 /***********************************************************************************************************************
 *  CanSM_CheckTransceiverWakeFlagIndication
 **********************************************************************************************************************/
/*! \brief      This callback function indicates the CheckTransceiverWakeFlag API process end for the notified CAN Transceiver.
 *  \param[in]  CanSM_TransceiverId     Requested Transceiver
 *  \pre        Input parameter must be valid.
 *  \context    Function could be called from interrupt level or from task level
 *  \note
 **********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_CheckTransceiverWakeFlagIndication( uint8 CanSM_TransceiverId );


/***********************************************************************************************************************
*  CanSM_ConfirmPnAvailability
**********************************************************************************************************************/
/*! \brief     This   callback   function   indicates   that   the   transceiver   is   running   in   PN communication mode.
*  \param[in]  CanSM_TransceiverId      CAN transceiver, which was checked for PN availability
*  \pre        Input parameter must be valid.
*  \context    Function could be called from interrupt level or from task level
*  \note
**********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_ConfirmPnAvailability ( uint8 CanSM_TransceiverId );


/***********************************************************************************************************************
 *  CanSM_TxTimeoutException
**********************************************************************************************************************/
/*! \brief     This callback function indicates that the CanNm has detected for the affected partial CAN network a tx timeout exception.
*  \param[in]  CanSM_NetworkHandle     Affected system channel
*  \pre        Input parameter must be valid.
*  \context    Function could be called from interrupt level or from task level
*  \note
**********************************************************************************************************************/
FUNC( void, CANSM_CODE ) CanSM_TxTimeoutException ( NetworkHandleType CanSM_NetworkHandle );


# define CANSM_STOP_SEC_CODE
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*******************************************************************************
* Organi check
*******************************************************************************/


#endif /* end if not defined ( CANSM_CBK_H ) */
/**********************************************************************************************************************
  END OF FILE: CanSm_Cbk.h
**********************************************************************************************************************/
/*  *****   STOPSINGLE_OF_MULTIPLE_COMMENT    *****  */

