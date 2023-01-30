/* STARTSINGLE_OF_MULTIPLE */


/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  Copyright (c) 2007-2014 by Vector Informatik GmbH.                                                  All rights reserved.
 
                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
         File:  ComM.H
    Component:  Communication Manager
       Module:  -
    Generator:  -

  Description:  API of the communication manager
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Thomas Kuhl                   Pet          Vector Informatik GmbH
  Daniel Hof                    Dhf          Vector Informatik GmbH
  Michael Schligerski           Mih          Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  01.00.ffb  2005-10-12  Pet                   first implementation
  01.00.ffc 2005-12-22  Alb                   prepare ComM.c to built libary
  01.FF.01 2006-06-20   Pet                   update to autosar spec. V2
                                              add BusOff handling
                                              add DCM communication request handling
  01.FF.02 2006-07-26   Pet                   change Dcm Cbk API and add prototypes
  01.FF.03 2006-08-15   Pet                   add support for FlexRay
  01.00.00 2006-12-04   Pet                   add EcuM run mode request/release
  01.01.00 2007-01-19   Pet                   adapt API for NM Asr R2.1
                                              add support for LIN
  01.02.00 2007-03-14   Pet                   change EcuM Run Mode request mechanism
                                              correct defines of code double sections
  01.03.00 2007-03-29   Pet                   advance ComM to support NM variant called light
  01.04.00 2007-07-05   Pet                   support NM Asr Release 1.0
  01.05.00 2007-07-24   Pet                   ESCAN00021574: ECU transmits only NULL frames
  02.00.FF 2007-07-25   Pet                   Update for ASR 2.1
           2007-09-12   Pet                   replace ComM_ReturnType by Std_ReturnType
                                              change ComM configuration struct
  02.00.00 2007-09-18   Pet                   Change handling of NM variants NONE and LIGHT
  03.00.00 2007-09-13   Pet                   support FlexRay State Manager
  04.00.00 2008-01-20   Pet                   change handling to support CanSM and LinSM
  04.01.00 2008-02-09   Pet     ESCAN00024821 Add Support for Bus wake up inhibition
                                ESCAN00024822 Add support for ComM Mode limitation
                                ESCAN00024823 Wrong ComM via function ComM_GetCurrentComMode
                                ESCAN00024824 network shutdown delay due to excecution on task level
                                ESCAN00024825 Ready sleep timer expires to early
  04.01.01 2008-02-29   Pet     ESCAN00024998: Missing prototype
  04.02.00 2008-02-29   Pet     ESCAN00025443: Add Compiler Apstraction and Memory mapping
                                ESCAN00025444: wrong Bus state manager mode indication function
  04.03.00 2008-03-25   Pet     ESCAN00025697: Add DEM error notification
  04.04.00 2008-04-03   Pet     ESCAN00025783: Add support for EcuM ASR3.0
  04.05.00 2008-04-11   Pet     ESCAN00026040: Compiler warning "Undefined macro 'ON'" occurs
                                ESCAN00026579: synchronous wake up via of CAN channles
                                ESCAN00026174: Link Time Checks
                                ESCAN00026706: Wrong communication mode via the API ComM_GetCurrentComMode
                                ESCAN00026858: Remove generated ComM Types
                                ESCAN00026865: Add additional critical sections
  04.06.00 2008-05-30   Dhf     ESCAN00027199: removed defines and added variable declaration
  04.07.00 2008-07-09   Pet     ESCAN00028339: ComM shall suport the shutdown out of every ComM state for FlexRay
  04.08.00 2008-08-04   Pet     ESCAN00029035: ComM_BusSM_ModeIndication wrong ComM mode Prameter 
                                ESCAN00028416: compiler waring in case of an defined but not used variable
                                ESCAN00027090: Support multiple user channel handling for ComM (one user N channels).
                                ESCAN00028423: Compile time optimization of DEM, DET Error Checks and Range Checks
                                ESCAN00029563: Compiler warning becaus of use C++ comments
                                ESCAN00029573: Variable ComM_InhibitCnt double defined
  04.09.00 2008-09-01   Pet     ESCAN00029998: PreCompile and Linktime Crc Check
                                ESCAN00030710: ComM does not wait for restart on FlexRay channels
                                ESCAN00030718: Move ComM_MainFunction from static code to generated source files
                                ESCAN00030719: Wrong DET error reported
                                ESCAN00030721: Add Ecu Passive Mode
                                ESCAN00030722: Optimization of source code size
  04.09.01 2008-11-05   Pet     ESCAN00031078: Compiler error: undeclared identifier
  04.10.00 2008-11-06   Pet     ESCAN00031338: ECU does not join after unsuccessful startup
                                ESCAN00031078: Compiler error: undeclared identifier
                                ESCAN00031953: Add ECU mode management support/User state change notification
                                ESCAN00030043: Ccl_AsrComM user state notification support
                                ESCAN00031333: Mode limitation to NO COMMUNICATION and Prevent Wakeup behavior does not work as expected
                                ESCAN00031902: LIN channel does not start communication
                                ESCAN00031906: Processing in function ComM_ResetInhibitCounter not aborted in case of un-initialized ComM
                                ESCAN00031943: added generator version check
                                ESCAN00031945: Compiler warning/error 'CanSM_SetEcuPassive' undefined
                                ESCAN00031946: Missing compiler abstraction
                                ESCAN00031920: Advance Misra compliance
  04.11.00 2009-02-16   Pet     ESCAN00033179: ECU switches to sleep in FULL_COMMUNICATION mode
                                ESCAN00032952: ComM does not start start up directly but waits on the BusSM during network start up
                                ESCAN00033554: Missing DCM Mode notification
                                ESCAN00033555: Missing ComM Mode notification
                                ESCAN00033471: Compiler Warning: variable "transitionStatus" is possibly uninitialized
                                ESCAN00033470: Compiler Warning: variable "calculatedComModeReq" is possibly uninitialized
                                ESCAN00033469: Compiler Warning: condition is always true
                                ESCAN00033566: Inhibition counter not incremented
  04.12.00 2009-03-16   Pet     ESCAN00034045: Compiler Warning
                                ESCAN00032473: Compiler warning
                                ESCAN00033353: Add support for ComMTMinFullComModeDuration in single channel OSEK NM configurations
                                ESCAN00034127: Remove ECU Passive Handling
                                ESCAN00031981: Resolve Misra violations
                                ESCAN00034182: Version number shall be bcd coded
  04.13.00 2009-07-07   Pet     ESCAN00036094: pre-processor checks for building the library
                                ESCAN00034726: Wrong ComM API return value if the ComM is not initialized
                                ESCAN00036368: Wrong parameter check
                                ESCAN00036399: change parameter list of internal ComM_DcmIndication
                                ESCAN00036409: Change ComM_BusType definition
  04.13.01 2009-11-27   Pet     ESCAN00039476: Storage of non volatile values not possible as required by NvRam-Manager
  04.14.00 2010-02-03   Pet     ESCAN00040730: ComM ASR 3.x extension for BAC2.1
  04.15.00 2010-04-06   Pet     ESCAN00040729: BETA version - no series production allowed
                                ESCAN00042605: undo changes for ESCAN00040730
  04.16.00 2010-08-04   Pet     ESCAN00040131: Support Bus Type Ethernet (Eth)
                                ESCAN00044524: ECU performs shutdown although communication stack is not in NO COMMUNICATION
                                ESCAN00044576: limited ECU communication capability because of wrong ComM prevent wake up state
                                ESCAN00044578: ComM initialization state not initialized within start up code
                                ESCAN00044579: Remove unnecessary pre-initialization inside ComM_InitMemory
  04.16.01 2010-08-04   Pet     ESCAN00047254: Channel is kept awake although no internal or external communication need
                                ESCAN00047570: Channel is kept awake although no internal or external communication need
  04.17.00 2010-12-10   Pet     ESCAN00047254: Channel is kept awake although no internal or external communication need
                                ESCAN00047570: Channel is kept awake although no internal or external communication need
                                ESCAN00046227: Adapt AUTOSAR version check
                                ESCAN00045648: Compiler warning: dead assignment to "calculatedComModeReq" eliminated
  04.17.01 2011-02.28   Pet     ESCAN00048960: Compiler/Linker warning/error 
  04.17.02 2011-05-11   Pet     ESCAN00049808: no changes here
  04.18.00 2011-05-23   Pet     ESCAN00051662: Remove the AUTOSAR Release Version Check
                                ESCAN00049808: Communication is always kept awake even if no internal or external communication needed
                                ESCAN00052478: Compiler Error:  "EcuM_ChannelHandleType" undeclared identifier
                                ESCAN00050281: Add Support for partial networking
  04.19.00 2011-08-19   Pet     ESCAN00050281: Add Support for partial networking
  04.20.00 2011-11-25   Pet     ESCAN00053619: Compiler error for ComMActiveIdentityMask (only Multiple Configuration)
                                ESCAN00053581: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
                                ESCAN00055410: Communication is always kept awake even if no internal or external communication needed
                                ESCAN00055413: Multiple user mode notification for the same ComM mode
  04.20.01 2012-02-23   Mih     ESCAN00055412: no changes here
                                ESCAN00055542: no changes here
  04.21.00 2012-04-05   Mih     ESCAN00057826: no changes here
                                ESCAN00055590: no changes here
                                ESCAN00054786: no changes here
                                ESCAN00058158: no changes here
  04.21.01 2012-06-21   Mih     ESCAN00059391: no changes here
                                ESCAN00056974: no changes here
  04.22.00 2012-09-21   Mih     ESCAN00059454: no changes here
                                ESCAN00061402: no changes here
                                ESCAN00060976: no changes here
                                ESCAN00060977: no changes here
  04.23.00 2013-04-12   Mih     ESCAN00061242: no changes here
                                ESCAN00061901: no changes here
                                ESCAN00062631: no changes here
                                ESCAN00065332: no changes here
                                ESCAN00066116: no changes here
                                ESCAN00066498: AR3-2426: Add possibility to deactivate PN functionality at runtime
                                ESCAN00066776: no changes here
  04.23.01 2013-09-19   Mih     ESCAN00069051: no changes here
  04.24.00 2014-01-31   Mih     ESCAN00071992: no changes here
                                ESCAN00073286: no changes here
                                ESCAN00073296: no changes here
**********************************************************************************************************************/

#ifndef COMM_H
#define COMM_H

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "ComM_Lcfg.h"                /* Include ComM configuration header */

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/* ##V_CFG_MANAGEMENT ##CQProject : Ccl_AsrComM CQComponent : Implementation */
#define CCL_ASRCOMM_VERSION             0x0424
#define CCL_ASRCOMM_RELEASE_VERSION     0x00

/* Version number */
#define COMM_SW_MAJOR_VERSION    (CCL_ASRCOMM_VERSION >> 8u)
#define COMM_SW_MINOR_VERSION    (CCL_ASRCOMM_VERSION & 0x00FF)
#define COMM_SW_PATCH_VERSION    CCL_ASRCOMM_RELEASE_VERSION

#define COMM_AR_MAJOR_VERSION    2u
#define COMM_AR_MINOR_VERSION    0u
#define COMM_AR_PATCH_VERSION    0u

#define COMM_VENDOR_ID          30u
#define COMM_MODULE_ID          12u

/* DET Error definitions */
#define COMM_E_NOT_INITED                 0x01u            /* API service used without module initialization */
#define COMM_E_WRONG_PARAMETERS           0x02u            /* API service used with wrong parameters */
#define COMM_E_ERROR_IN_PROV_SERVICE      0x03u            /* provided API services of other module returns with an error */
#define COMM_E_NOSUPPORTED_MODECHANGE     0x04u            /* the ComM performs a not allowed state transition */


/* Service ID */
#define COMM_INIT_ID                      0x01u
#define COMM_DEINIT_ID                    0x02u
#define COMM_GETSTATUS_ID                 0x03u
#define COMM_GETINHIBITIONSTATUS_ID       0x04u
#define COMM_REQUESTCOMMODE_ID            0x05u
#define COMM_GETMAXCOMMODE_ID             0x06u
#define COMM_GETREQUESTEDCOMMODE_ID       0x07u
#define COMM_GETCURRENTCOMMODE_ID         0x08u
#define COMM_PREVENTWAKEUP_ID             0x09u
#define COMM_LIMITCHANNELTONOCOMMODE_ID   0x0Bu
#define COMM_LIMITECUTONOCOMMODE_ID       0x0Cu
#define COMM_READINHIBITCOUNTER_ID        0x0Du
#define COMM_RESETINHIBITCOUNTER_ID       0x0Eu
#define COMM_SETECUGROUPCLASSIFICATION_ID 0x0Fu
#define COMM_GETVERSIONINFO_ID            0x10u
#define COMM_DISABLEPNACTIVATIONSTATE_ID  0x11u
#define COMM_MAINFUNCTION_ID              0x60u
#define COMM_DCM_SETPASSIVEMODE_ID        0x70u

/* callback function service ID */
#define COMM_CBK_NM_NETWORKSTARTINDICATION_ID  0x15u
#define COMM_CBK_NM_NETWORKMODE_ID             0x18u
#define COMM_CBK_NM_PREPAREBUSSLEEPMODE_ID     0x19u
#define COMM_CBK_NM_BUSSLEEPMODE_ID            0x1Au
#define COMM_CBK_NM_RESTARTINDICATION_ID       0x1Bu
#define COMM_CBK_DCM_ACTIVEDIAGNOSTIC_ID       0x1Fu
#define COMM_CBK_DCM_INACTIVEDIAGNOSTIC_ID     0x20u
#define COMM_CBK_ECUM_RUNMODEINDICATION_ID     0x29u
#define COMM_CBK_ECUM_WAKEUPINDICATION_ID      0x2Au
#define COMM_CANSM_MODEINDICATION_ID           0x33u
#define COMM_LINSM_MODEINDICATION_ID           0x33u
#define COMM_FRSM_MODEINDICATION_ID            0x33u

/* Service defines for the ComM state transitions */
#define COMM_NEXT_TRANS    0x01u 
#define COMM_END_TRANS     0x02u
#define COMM_STUP_DEACTIVE 0x01u
#define COMM_STUP_ACTIVE   0x02u
#define COMM_NO_STATE_CHANGE 0x10u


/* Service defines for the handling of the BusSM */
#define COMM_BUSSM_NO_REQ       4u
#define COMM_BUSSM_SILENT_REQ   5u
#define COMM_BUSSM_FULL_REQ     6u


/* defines to identify the configured NM variant */
#define NM_VARIANT_FULL       1u
#define NM_VARIANT_PASSIVE    2u
#define NM_VARIANT_LIGHT      3u
#define NM_VARIANT_NONE       4u
#define NM_VARIANT_OSEK       5u


/* advanced return type of the communication manager */
#define COMM_E_MODE_LIMITATION        2u                  /* mode is limited and can not be requested by the ComM User */
#define COMM_E_UNINIT                 3u                  /* API called but ComM is not initialized */


/* inhibition service defines */
#define COMM_INHIBITION_BUS_WAKEUP    (uint8)0x01
#define COMM_INHIBITION_NO_COM        (uint8)0x02


/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
/* PRQA S 3453 1 */ /* MD_ComM_3453 */
#  define ComM_Assert(ErrCode, ApiId)   Det_ReportError( 12, 0, (uint8)(ApiId), (uint8)(ErrCode) )
#else
#  define ComM_Assert(ErrCode, ApiId)
#endif

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)

#define COMM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/* PRQA S 0781 1 */ /* MD_ComM_0781 */
extern VAR(uint16, COMM_VAR_NOINIT) ComM_ActiveIdentityMask;

#define COMM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#endif

#if  ( STD_OFF == COMM_IDENTITY_MANAGER_CONFIG )
# define COMM_START_SEC_PBCFG_ROOT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(ComM_ConfigType, COMM_PBCFG) ComMConfig;

# define COMM_STOP_SEC_PBCFG_ROOT
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/**********************************************************************************************************************
  INTERNAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COMM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern FUNC(void, COMM_CODE) ComM_MainFunction(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COMM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* initialization function of the ComM */
FUNC(void, COMM_CODE)  ComM_Init( P2CONST( ComM_ConfigType, AUTOMATIC, COMM_PBCFG ) ConfigPtr );

/* initialization of ComM memory */
extern FUNC(void, COMM_CODE) ComM_InitMemory(void);

/* de-initialization function of the ComM */
extern FUNC(void, COMM_CODE) ComM_DeInit(void);

/* gets the ComM status */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus(P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_APPL_VAR) Status);

/* request a communication mode for an User */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComMode(ComM_UserHandleType User, ComM_ModeType ComMode);

/* Get the maximum allowed communication mode of an User */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetMaxComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode);

/* Get the requested communication mode of an user */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetRequestedComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode);

/* Get the current communication mode of an user */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurrentComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode);

/* Get the current inhibition status */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetInhibitionStatus( NetworkHandleType Channel, P2VAR(ComM_InhibitionStatusType, AUTOMATIC, COMM_APPL_VAR) Status);

/* set the prevent wake up state */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_PreventWakeUp( NetworkHandleType Channel, boolean Status);

/* set the inhibition state to no communication */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode( NetworkHandleType Channel, boolean Status);

/* limt the ECU to no communication mode */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode(boolean Status);

/* read the full communication inhibit counter */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter(P2VAR(uint16, AUTOMATIC, COMM_APPL_VAR) CounterValue);

/* reset the full communication inhibit counter */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter(void);

/* set the ECU group calssification */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status);

#  if (COMM_VERSION_INFO_API == STD_ON)
/* get component piblished information */
extern FUNC(void, COMM_CODE) ComM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COMM_APPL_VAR) versioninfo);
#  endif

extern FUNC(boolean, COMM_CODE) ComM_NoComLimitationActive( NetworkHandleType  Channel );

# if ( COMM_PNC_SUPPORT == STD_ON )
/* API to disable PNC functionality at runtime during BSW initialization */
extern FUNC(void, COMM_CODE) ComM_DisablePNActivationState(void);
# endif

#define COMM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#endif  /* COMM_H */

/**********************************************************************************************************************
  END OF FILE: ComM.H
**********************************************************************************************************************/
/* STOPSINGLE_OF_MULTIPLE */
