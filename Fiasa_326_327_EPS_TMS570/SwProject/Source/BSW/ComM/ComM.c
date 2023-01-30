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
         File:  ComM.C
      Project:  Communication Manager
       Module:  -
    Generator:  -

  Description:  Implementation of the Autosar Communication Manager
**********************************************************************************************************************/

/**********************************************************************************************************************
  AUTHOR IDENTITY
-----------------------------------------------------------------------------------------------------------------------
  Name                          Initials      Company
-----------------------------------------------------------------------------------------------------------------------
  Thomas Kuhl                   Pet           Vector Informatik GmbH
  Daniel Hof                    Dhf           Vector Informatik GmbH
  Michael Schligerski           Mih           Vector Informatik GmbH
-----------------------------------------------------------------------------------------------------------------------
  REVISION HISTORY
-----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Change Id     Description
-----------------------------------------------------------------------------------------------------------------------
  01.00.ffb 2005-10-12  Pet                   first implementation
  01.00.ffc 2005-12-22  Alb                   prepare ComM.c to built libary
  01.FF.01 2006-06-20   Pet                   update to autosar spec. V2
                                              add BusOff handling
                                              add DCM diagnositic session handling
                                              add API ComM_GetVersionInfo
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
  03.FF.00 2007-10-03   Pet                   support CAN State Manager
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
                                ESCAN00046772: Support Multiple Identity Configuration
  04.17.01 2011-02.28   Pet     ESCAN00048960: Compiler/Linker warning/error 
  04.17.02 2011-05-11   Pet     ESCAN00049808: Communication is always kept awake even if no internal or external communication needed
  04.18.00 2011-05-23   Pet     ESCAN00051662: Remove the AUTOSAR Release Version Check
                                ESCAN00049808: Communication is always kept awake even if no internal or external communication needed
                                ESCAN00052478: Compiler Error:  "EcuM_ChannelHandleType" undeclared identifier
                                ESCAN00050281: Add Support for partial networking
  04.19.00 2011-08-19   Pet     ESCAN00050281: Add Support for partial networking
  04.20.00 2011-11-25   Pet     ESCAN00053619: Compiler error for ComMActiveIdentityMask (only Multiple Configuration)
                                ESCAN00053581: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
                                ESCAN00055410: Communication is always kept awake even if no internal or external communication needed
                                ESCAN00055413: Multiple user mode notification for the same ComM mode
  04.20.01 2012-02-23   Mih     ESCAN00055412: Partial network request is not communicated
                                ESCAN00055542: Communication on partial network is requested
  04.21.00 2012-04-05   Mih     ESCAN00057826: Compiler warning: unused parameter 'ConfigPtr'
                                ESCAN00055590: Change of Nm variant 'NONE' handling
                                ESCAN00054786: ComM mode limitation is performed rightless
                                ESCAN00058158: Remove unused parameter of the function ComM_PncStateChangeNotification()
  04.21.01 2012-06-21   Mih     ESCAN00059391: Internal ComM state not displayed correctly by XCP/AMD
                                ESCAN00056974: no changes here
  04.22.00 2012-09-21   Mih     ESCAN00059454: AR3-2398: Update Partial Network Handling according ASR3.2.2
                                ESCAN00061402: Add support of ComMPncNmRequest parameter
                                ESCAN00060976: PNC does not enter No Communication mode again when Pnc Prepare Sleep Timer is 0 and external wake-up
                                ESCAN00060977: ECU does not enter sleep when a PNC is requested and released after an external wake-up
  04.23.00 2013-04-12   Mih     ESCAN00061242: Shutdown synchronisation is shortened or delayed depending on timing conditions
                                ESCAN00061901: NM Message Reception in Silent Mode leads to DET error and missing NM Tx Message
                                ESCAN00062631: The ECU (Dcm) does not respond to a diagnostic request after re-programming according to HIS
                                ESCAN00065332: ECU does not send Nm messages on a channel while ComM channel user requests FULL_COM
                                ESCAN00066116: AR3-2494: Implement AMD timemeasurement support
                                ESCAN00066498: AR3-2426: Add possibility to deactivate PN functionality at runtime
                                ESCAN00066776: Network with partial networking does not enter sleep
  04.23.01 2013-09-19   Mih     ESCAN00069051: AR3-2562: First message after restart or startup must be the Nm message
  04.24.00 2014-01-31   Mih     ESCAN00071992: MISRA deviation: MISRA-C:2004 Rule 1.2
                                ESCAN00073286: Performance improvement for gateways with Partial Networking
                                ESCAN00073296: MISRA deviation: MISRA-C:2004 Code Metrics
**********************************************************************************************************************/

#define CCL_ASR_COMM_SOURCE /* ESCAN00066116 */

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "ComM.h"                                     /* Include Commmunication Manager */
#include "SchM_ComM.h"
#include "EcuM.h"                                     /* Include Ecu Manager */
#include "ComM_Nm.h"
#include "ComM_EcuM.h"
#include "ComM_BusSM.h"
#include "ComM_Dcm.h"
#if (COMM_PNC_SUPPORT == STD_ON)
#include "BswM_ComM.h"
#include "Nm.h"
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
#  include "Det.h"
#endif

#if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
# include "v_ver.h"
#endif

#if ((!defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )) || ( COMM_CRC_CHECK == STD_ON ))
#include "EcuM_Cbk.h"
#endif

#if ( COMM_AMD_RUNTIME_MEASUREMENT == STD_ON ) /* ESCAN00066116 */
# include "AmdRtm.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if ( COMM_SW_MAJOR_VERSION != 0x04u )
# error "ComM Source and Header files are inconsistet!"
#endif

#if ( COMM_SW_MINOR_VERSION != 0x24u)
# error "ComM Source and Header files are inconsistet!"
#endif

#if ( COMM_SW_PATCH_VERSION != 0x0u )
# error "ComM Source and Header files are inconsistet!"
#endif

/* ComM BusSM header version check */
#if ( COMM_BUSSM_MAJOR_VERSION != 4u )
 #error "Source and Header file ComM_BusSM.h are inconsistent (COMM_BUSSM_MAJOR_VERSION)!"
#endif

#if ( COMM_BUSSM_MINOR_VERSION != 24u)
# error "Source and Header file ComM_BusSM.h are inconsistent (COMM_BUSSM_MINOR_VERSION)!"
#endif

#if ( COMM_BUSSM_PATCH_VERSION != 0u )
# error "Source and Header file ComM_BusSM.h are inconsistent (COMM_BUSSM_PATCH_VERSION)!"
#endif

/* ComM DCM header version check */
#if ( COMM_DCM_MAJOR_VERSION != 4u )
 #error "Source and Header file ComM_Dcm.h are inconsistent (COMM_DCM_MAJOR_VERSION)!"
#endif

#if ( COMM_DCM_MINOR_VERSION != 24u)
# error "Source and Header file ComM_Dcm.h are inconsistent (COMM_DCM_MINOR_VERSION)!"
#endif

#if ( COMM_DCM_PATCH_VERSION != 0u )
# error "Source and Header file ComM_Dcm.h are inconsistent (COMM_DCM_PATCH_VERSION)!"
#endif


/* ComM EcuM header version check */
#if ( COMM_ECUM_MAJOR_VERSION != 4u )
 #error "Source and Header file ComM_EcuM.h are inconsistent (COMM_ECUM_MAJOR_VERSION)!"
#endif

#if ( COMM_ECUM_MINOR_VERSION != 24u)
# error "Source and Header file ComM_EcuM.h are inconsistent (COMM_ECUM_MINOR_VERSION)!"
#endif

#if ( COMM_ECUM_PATCH_VERSION != 0u )
# error "Source and Header file ComM_EcuM.h are inconsistent (COMM_ECUM_PATCH_VERSION)!"
#endif


/* ComM NM header version check */
#if ( COMM_NM_MAJOR_VERSION != 4u )
 #error "Source and Header file ComM_Nm.h are inconsistent (COMM_NM_MAJOR_VERSION)!"
#endif

#if ( COMM_NM_MINOR_VERSION != 24u)
# error "Source and Header file ComM_Nm.h are inconsistent (COMM_NM_MINOR_VERSION)!"
#endif

#if ( COMM_NM_PATCH_VERSION != 0u )
# error "Source and Header file ComM_Nm.h are inconsistent (COMM_NM_PATCH_VERSION)!"
#endif

/* ComM Types header version check */
#if ( COMM_TYPES_MAJOR_VERSION != 4u )
 #error "Source and Header file ComM_Types.h are inconsistent (COMM_TYPES_MAJOR_VERSION)!"
#endif

#if ( COMM_TYPES_MINOR_VERSION != 24u)
# error "Source and Header file ComM_Types.h are inconsistent (COMM_TYPES_MINOR_VERSION)!"
#endif

#if ( COMM_TYPES_PATCH_VERSION != 0u )
# error "Source and Header file ComM_Types.h are inconsistent (COMM_TYPES_PATCH_VERSION)!"
#endif

#if defined (V_EXTENDED_BUILD_LIB_CHECK)
 /**********************************************************************************************************************
 *  BUILD LIB CHECK
 *********************************************************************************************************************/
#  if (COMM_CONFIG_VARIANT == 0x01u)
#    error "ComM: It is not allowed to create a library with configured configuration variant PRE-COMPILE!"
#  endif
#endif


/**********************************************************************************************************************
  COMPATIBILITY / DEFAULTS
**********************************************************************************************************************/

#if !defined (V_USE_DUMMY_STATEMENT)
# error "The define V_USE_DUMMY_STATEMENT shall be defined either in Compiler_Cfg.h or as parameter for the Compiler"
#endif

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  FILE LOCAL DEFINES
**********************************************************************************************************************/
#define NO_TRANSMI  (uint8)0xff     /* no transition */
#define NO_COM      (ComM_SubModeType)0x00     /* no commuincation mode shutdown */
#define SI_COM      (ComM_SubModeType)0x01     /* silent com network released */
#define FU_RED_SLE  (ComM_SubModeType)0x02     /* full com ready to sleep */
#define FU_REQ_NET  (ComM_SubModeType)0x03     /* full com network requested */

#define COMM_FR_SHUTDOWN_ACTIVE     (uint8)0x00
#define COMM_FR_SHUTDOWN_DEACTIVE   (uint8)0x01


/**********************************************************************************************************************
  FILE LOCAL FUNCTION MACROS
**********************************************************************************************************************/
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
/* PRQA S 3458 1 */ /* MD_MSR_19.4  */
#  define ComM_CheckInitStatus(ApiId, ErrCode, retValue)   { if(ComM_InitStatus == COMM_UNINIT) {  Det_ReportError( 12, 0, (uint8)(ApiId), (uint8)(ErrCode)); (retValue) = COMM_E_UNINIT; } }
#else
#  define ComM_CheckInitStatus(ApiId, ErrCode, retValue)
#endif

/* ESCAN00057826: dummy (void) cast for unused function parameters in order to avoid compiler warnings */
#if ( V_USE_DUMMY_STATEMENT == STD_ON )
/* PRQA S 3458 1 */ /* MD_MSR_19.4  */
#   define ComM_DummyStatement(unusedParameter)   { (void)(unusedParameter); }
#else
#   define ComM_DummyStatement(unusedParameter)
#endif

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/* type definition of the ComM transition function call table */
typedef P2FUNC(void, COMM_CODE, ComM_TransitionFunctionType) (NetworkHandleType  Channel);


/**********************************************************************************************************************
  ROM DATA
**********************************************************************************************************************/
#define COMM_START_SEC_CONST_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* ComM transition table [Requested][Active]*/
/* PRQA S 3218 1 */ /* MD_ComM_3218 */
STATIC CONST(uint8, COMM_CONST) ComM_TransitionTable[4][4] =    /* [row] [column] */
{/* active|NO_COM    | SI_COM    | FU_RED_SLE| FU_REQ_NET  requested mode: */ 
          {NO_TRANSMI, NO_COM,     SI_COM,     FU_RED_SLE}, /* NO_COM     */
          {NO_TRANSMI, NO_TRANSMI, SI_COM,     FU_RED_SLE}, /* SI_COM     */
          {FU_RED_SLE, FU_RED_SLE, NO_TRANSMI, FU_RED_SLE}, /* FU_RED_SLE */
          {FU_REQ_NET, FU_REQ_NET, FU_REQ_NET, NO_TRANSMI}  /* FU_REQ_NET */
};

#define COMM_STOP_SEC_CONST_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#define COMM_START_SEC_CONST_32BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#if !defined(V_SUPPRESS_EXTENDED_VERSION_CHECK)
CONST( uint32, COMM_CONST ) CCL_ASRCOMM_LIB_SYMBOL = CCL_ASRCOMM_LIB_VERSION;
#endif

#define COMM_STOP_SEC_CONST_32BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* ComM transition action table [new][current] */
/* PRQA S 3218 1 */ /* MD_ComM_3218 */
STATIC CONST(ComM_TransitionFunctionType, COMM_CONST) ComM_TransitionFctTable[4][4] =
{/*|NO_COM    |        SI_COM             |FU_RED_SLE|         FU_REQ_NET           current requested mode: */
   {ComM_NO_TRANS,     ComM_SICOM_NOCOM,  ComM_SICOM,          ComM_NETREQ_READYS}, /* NO_COM     */
   {ComM_NO_TRANS,     ComM_NO_TRANS,     ComM_SICOM,          ComM_NETREQ_READYS}, /* SI_COM     */
   {ComM_NOCOM_READYS, ComM_SICOM_READYS, ComM_NO_TRANS,       ComM_NETREQ_READYS}, /* FU_RED_SLE */
   {ComM_NOCOM_NETREQ, ComM_SICOM_NETREQ, ComM_READYS_NETREQ,  ComM_NO_TRANS}       /* FU_REQ_NET */
};

#define COMM_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"
/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)

#define COMM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

VAR(uint16, COMM_VAR_NOINIT) ComM_ActiveIdentityMask;

#define COMM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#endif

/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
#define COMM_START_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

STATIC VAR(boolean, COMM_VAR_NOINIT_8BIT)      ComM_DcmRequestActive;  /* DCM request flag */

#if (COMM_PNC_SUPPORT == STD_ON)
/* The flag signals, if a mode notification to PNC users is needed due to a PNC state change.
 * TRUE - a PNC changed the state from FULL_COM to NO_COM or vice versa or the last mode notification failed,
 * FALSE (default) - no PNC state changes to be notified and the last mode notification was succsessfull. */
STATIC VAR(boolean, COMM_VAR_NOINIT_8BIT)      ComM_NotifyPncStateChange;
#endif

#define COMM_STOP_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define COMM_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"
STATIC VAR( ComM_InitStatusType, COMM_VAR_ZERO_INIT) ComM_InitStatus = COMM_UNINIT;              /* ComM status */  /* ESCAN00044578 */
#define COMM_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define COMM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

STATIC FUNC( ComM_SubModeType, COMM_CODE) ComM_CalculateHighestComMode( NetworkHandleType  Channel);
STATIC FUNC(boolean, COMM_CODE) ComM_PreventWakeUpActive( NetworkHandleType  Channel );

#if (COMM_PNC_SUPPORT == STD_ON)
STATIC FUNC(void, COMM_CODE) ComM_PNModeArbitration(NetworkHandleType Channel);
STATIC FUNC(ComM_PncModeType, COMM_CODE) ComM_CalculateHighestPNComMode( uint8 PN, NetworkHandleType  Channel );
#endif

/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/

/*********************************************************************************************************************
  FUNCTION: ComM_Init
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: Ecu Manager
  Precondition: -

  Initializes the communication manager and the communication stack.
*********************************************************************************************************************/
FUNC(void, COMM_CODE)  ComM_Init( P2CONST( ComM_ConfigType, AUTOMATIC, COMM_PBCFG ) ConfigPtr )
{
  uint8 ComM_Channel;
  uint8 ComM_ByteIndex;
  uint8 ComM_User;
  Std_ReturnType retNvM;

#if (COMM_PNC_SUPPORT == STD_ON)
  uint8 ComM_PnIdx;
  uint8 ComM_PncSignalByte;
  uint8 ComM_PncBusType;
#endif

#  if ( COMM_DEV_ERROR_DETECT == STD_ON )
  if (ConfigPtr == NULL_PTR)
  { 
    ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_INIT_ID);
  }
#  endif

#if ( COMM_CRC_CHECK == STD_ON )
  /* PRQA S 0505 1 */ /* MD_ComM_0505 */ /* ESCAN00031078 */
  if (ConfigPtr->ComM_PrecompileCRC != COMM_PRECOMPILE_CRC)
  {
    EcuM_GeneratorCompatibilityError((uint16) COMM_MODULE_ID, (uint8) 0u);
    return;
  }
#endif

#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
    if(((ConfigPtr->ComM_GeneratorVersion & 0x00FFFF00)!=
      (((uint32)CCL_ASRCOMM_GENTOOL_GENY_MAJOR_VERSION<<16) | ((uint32)CCL_ASRCOMM_GENTOOL_GENY_MINOR_VERSION<<8)))
#  if defined(CCL_ASRCOMM_GENTOOL_GENY_PATCH_VERSION)
#    if(CCL_ASRCOMM_GENTOOL_GENY_PATCH_VERSION != 0)
      || ((ConfigPtr->ComM_GeneratorVersion & 0x000000FF) < CCL_ASRCOMM_GENTOOL_GENY_PATCH_VERSION)
#    endif
#  endif
      )
    {
      EcuM_GeneratorCompatibilityError((uint16) COMM_MODULE_ID, (uint8) 0);
      return; /* Do not continue with the initialization of the component the Application may be influenced critically. */
    }
#endif


  ComM_DcmRequestActive = FALSE;  /* no DCM request is pendign */
  ComM_LastModeIndicatedToDcm = COMM_NO_COMMUNICATION; /* ESCAN00062631 */

  retNvM = ComM_LoadNonVolatileValues();

#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  /* PRQA S 0505 1 */ /* MD_ComM_0505 */
  ComM_ActiveIdentityMask = ConfigPtr->ComM_ActiveIdentityMask;
#endif

  if(retNvM == E_NOT_OK)
  {
    ComM_Inhibition.ComM_ECUGroupClassification = ComM_ECUGroupClassInit;  /* initialize the ECU group classification with the configured value */ 
    ComM_Inhibition.ComM_InhibitCnt             = 0x00;                    /* reset the inhibition counter */
  }

  for( ComM_User = 0; ComM_User < ComM_MaxNumberOfUsers; ComM_User++)
  {
    ComM_LastStateChange[ComM_User] = COMM_NO_COMMUNICATION;
  }

  for(ComM_Channel=0; ComM_Channel < ComM_Active_Channel; ComM_Channel++)
  {
    ComM_BusComModeReq[ComM_Channel] = NO_COM;                       /* reset the bus communication request flag */
    ComM_BusComModeReqTmp[ComM_Channel] = NO_COM;                       /* reset the bus communication request flag */
    ComM_ActiveComMode[ComM_Channel] = NO_COM;                       /* set the ComM mode NO Communication */
    
    ComM_BusSmState[ComM_Channel] = COMM_NO_COMMUNICATION;
    ComM_LastBusSmState[ComM_Channel] = COMM_NO_COMMUNICATION;

    ComM_MinFullComModeTime[ComM_Channel] = 0x00;                         /* minimum full communiation mode duration time */
    ComM_NmLightTimeout[ComM_Channel] = 0x00;                             /* timer after ready sleep mode is left */
    ComM_FrShutdown[ComM_Channel] = COMM_FR_SHUTDOWN_DEACTIVE;            /* deactivate the flexray shutdown flag */
    ComM_StateChange[ComM_Channel] = COMM_NO_STATE_CHANGE;

#if (COMM_PNC_SUPPORT == STD_ON)
    for( ComM_PncSignalByte = 0u; ComM_PncSignalByte < COMM_PNC_SIGNAL_LENGTH_BYTES; ComM_PncSignalByte++ )
    {
      ComM_IRSignal[ComM_Channel][ComM_PncSignalByte] = 0x00u;
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
      EraValues[ComM_Channel][ComM_PncSignalByte] = 0x00u;
# endif
    }
#endif

    /* ESCAN00044576 */
    if(retNvM == E_NOT_OK)
    {
      ComM_Inhibition.ComM_InhibitionStatus[ComM_Channel] = ComM_InhibitionStatusInitValue[ComM_Channel];  /* initialize the prevent wake up and mode limitation with the configured values */
    }
    else
    {
      ComM_Inhibition.ComM_InhibitionStatus[ComM_Channel] |= (uint8)(ComM_InhibitionStatusInitValue[ComM_Channel] & 0xFE);  /* initialize the mode limitation with the configured values */
    }
  }

  /* initialize the ComM mode request variables */
  for(ComM_ByteIndex=0; ComM_ByteIndex < ComM_User_ByteCount; ComM_ByteIndex++)
  {
    ComM_UserReqFullComArray[ComM_ByteIndex]   = (uint8)0x00; /* clear full com request field */
  }

#if (COMM_PNC_SUPPORT == STD_ON)
  for(ComM_ByteIndex=0; ComM_ByteIndex < ComM_User_PncByteCount; ComM_ByteIndex++)
  {
    ComM_UserReqPncFullCom[ComM_ByteIndex] = (uint8)0x00; /* clear full com request field */
  }

  for(ComM_PnIdx=0; ComM_PnIdx < COMM_ACTIVE_PNC; ComM_PnIdx++)
  {
    ComM_PncPSleepTimer[ComM_PnIdx] = 0;
    ComM_ActivePncComMode[ComM_PnIdx] = COMM_PNC_NO_COMMUNICATION;
    ComM_BusPncComModeReq[ComM_PnIdx] = COMM_PNC_NO_COMMUNICATION;
  }
  /* PRQA S 0505 1 */ /* MD_ComM_0505 */
  ComM_PncEnabled = ConfigPtr->ComM_PartialNetwork;

  /* Eira signal values are stored per bus type supporting PNC - currently CAN and FR */
  for( ComM_PncBusType = 0u; ComM_PncBusType < COMM_PNC_NUMBER_OF_BUSTYPES; ComM_PncBusType++ )
  {
    for( ComM_PncSignalByte = 0u; ComM_PncSignalByte < COMM_PNC_SIGNAL_LENGTH_BYTES; ComM_PncSignalByte++ )
    {
      EiraValues[ComM_PncBusType][ComM_PncSignalByte] = 0x00u;
    }
  }
  
  ComM_NotifyPncStateChange = FALSE;
#endif

/* ESCAN00057826 */
#if (( COMM_DEV_ERROR_DETECT == STD_ON ) || \
     ( COMM_CRC_CHECK == STD_ON ) || \
     !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK ) || \
     (COMM_IDENTITY_MANAGER_CONFIG == STD_ON) || \
     (COMM_PNC_SUPPORT == STD_ON))
#else
  ComM_DummyStatement( ConfigPtr ) /* PRQA S 3112 */ /* MD_ComM_3112 */
#endif

  /* initialization of communication stack */
  ComM_InitStatus = COMM_INIT;  /* ComM is initialized */

  /* PRQA S 2006 1 */ /* MD_MSR_14.7 */
} /* PRQA S 6010, 6030 */ /* MD_MSR_STPTH, MD_MSR_STCYC */

/*********************************************************************************************************************
  FUNCTION: ComM_DeInit
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: Ecu Manager
  Precondition: De-Init shall only be performed if the ComM is in " No Communication" state.

  De-Initialize the communication manager, the communication modules including the network management.
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_DeInit(void)
{
  ComM_InitStatus = COMM_UNINIT;  /* ComM is not initialized */
}


/*********************************************************************************************************************
  FUNCTION: ComM_InitMemory
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: Ecu Manager
  Precondition: 

  Initialize the ComM variables which are could be used if the ComM is not initialized.
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_InitMemory(void)
{
  ComM_InitStatus = COMM_UNINIT;  /* ComM is not initialized */
}


/*********************************************************************************************************************
  FUNCTION: ComM_GetStatus
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: ComM_InitStatusType      Status                  communiction manager initialisation state
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the fucntion ComM_InitMemory()

  Returns the initialization state of the communication manager
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus( P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_APPL_VAR) Status)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  if(Status == NULL_PTR)
  {
    ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETSTATUS_ID);
    retValue = E_NOT_OK;
  }
  else
  {
#endif

    *Status = ComM_InitStatus;

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  }

  return retValue;
#else
  return E_OK;
#endif
}


/*********************************************************************************************************************
  FUNCTION: ComM_RequestComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: ComM_UserHandleType     User                    handle of the user how requests a mode
          ComM_ModeType           ComMode                 requested communication mode possible values are:
                                                          COMM_NO_COMMUNICATION
                                                          COMM_SILENT_COMMUNICATION
                                                          COMM_FULL_COMMUNICATION
  Output: -
  Return: Std_ReturnType                                   return value of ComM API
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Requesting of a communication mode by a user
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComMode(ComM_UserHandleType User, ComM_ModeType ComMode)
{
  Std_ReturnType retValue;
  uint8 iByteMaskIndex;
#if (COMM_PNC_SUPPORT == STD_ON)
#  if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  boolean bPncUsed;
#  endif
#endif

  retValue = E_OK;
#if (COMM_PNC_SUPPORT == STD_ON)
#  if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  bPncUsed = FALSE;
#  endif
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  ComM_CheckInitStatus(COMM_REQUESTCOMMODE_ID, COMM_E_NOT_INITED, retValue)  /* check the initialization state of the ComM */

  if(retValue == E_OK)
  {
    if(User < ComM_MaxNumberOfUsers) /* User handle is valid */
    {
#endif
      SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);
      switch(ComMode)
      {
        case COMM_NO_COMMUNICATION: 
          {
            /* clear bit for full request */
            for(iByteMaskIndex = ComM_UserByteMaskIndex[User]; iByteMaskIndex < ComM_UserByteMaskIndex[User+1]; iByteMaskIndex++)
            {
              ComM_UserReqFullComArray[ComM_UserByteMask[iByteMaskIndex].ByteIndex] &= ComM_UserByteMask[iByteMaskIndex].ClearMask;
            }
#if (COMM_PNC_SUPPORT == STD_ON)
            if(ComM_PncEnabled == TRUE)
            {
              if(ComM_PncUser[User] == TRUE)
              {
                /* clear bit for full request */
                for(iByteMaskIndex = ComM_UserPncByteMaskIndex[User]; iByteMaskIndex < ComM_UserPncByteMaskIndex[User+1]; iByteMaskIndex++)
                {
                  ComM_UserReqPncFullCom[ComM_UserPncByteMask[iByteMaskIndex].ByteIndex] &= ComM_UserPncByteMask[iByteMaskIndex].ClearMask;
                }
              }
            }
#endif
          }
        break;
        case COMM_FULL_COMMUNICATION:
          {
            /* set bit for full request */
            for(iByteMaskIndex = ComM_UserByteMaskIndex[User]; iByteMaskIndex < ComM_UserByteMaskIndex[User+1]; iByteMaskIndex++)
            {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
              if((ComM_IdentityMapping[ComM_UserByteMask[iByteMaskIndex].Channel] & ComM_ActiveIdentityMask) != 0u)
              {
#  if (COMM_PNC_SUPPORT == STD_ON)
                bPncUsed = TRUE;
#  endif
#endif
                ComM_UserReqFullComArray[ComM_UserByteMask[iByteMaskIndex].ByteIndex]    |= ComM_UserByteMask[iByteMaskIndex].SetMask;

                /* check if mode limitation to NO COM is active */
                /* PRQA S 3415 1 */ /* MD_ComM_3415 */
                if( (ComM_NoComLimitationActive(ComM_UserByteMask[iByteMaskIndex].Channel) == TRUE ) ||
                    ( ComM_PreventWakeUpActive(ComM_UserByteMask[iByteMaskIndex].Channel) == TRUE) )
                {
                  if(ComM_Inhibition.ComM_InhibitCnt < 65535)
                  {
                    ComM_Inhibition.ComM_InhibitCnt++;

                    /* trigger the storeage of non-volatile values */
                    ComM_StoreNonVolatileValues();
                  }

                  retValue = COMM_E_MODE_LIMITATION;
                }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
              }
#endif
            }
#if (COMM_PNC_SUPPORT == STD_ON)
#  if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
            if(bPncUsed == TRUE)
            {
#  endif
              if(ComM_PncEnabled == TRUE)
              {
                if(ComM_PncUser[User] == TRUE)
                {
                  for(iByteMaskIndex = ComM_UserPncByteMaskIndex[User]; iByteMaskIndex < ComM_UserPncByteMaskIndex[User+1]; iByteMaskIndex++)
                  {
                    ComM_UserReqPncFullCom[ComM_UserPncByteMask[iByteMaskIndex].ByteIndex]    |= ComM_UserPncByteMask[iByteMaskIndex].SetMask;
                  }
                }
              }
#  if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
            }
#  endif
#endif
          }
        break;
        default:
           /* DET info wrong commuincation mode */
          retValue = E_NOT_OK;
          ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_REQUESTCOMMODE_ID); 
        break;
      }
      SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
    }
    else /* user handle is invalid */
    {
      /* DET entry COMM_E_WRONG_PARAMETERS */
      retValue = E_NOT_OK;
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_REQUESTCOMMODE_ID); /* call assertion unknown user handle*/
    }
  }
#endif

  return retValue;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/*********************************************************************************************************************
  FUNCTION: ComM_GetMaxComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: ComM_UserHandleType     User                    user handle
          ComM_ModeType           *ComMode                max allowed communication mode
  Output: ComM_ModeType           *ComMode                max allowed communication mode
  Return: Std_ReturnType                                  return value of ComM API
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to query the maximum allowed communication mode of the corresponding user.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_GetMaxComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode)
{
  uint8 iByteMaskIndex;
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  boolean bUserActive;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;
#endif

#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  bUserActive = FALSE;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  ComM_CheckInitStatus(COMM_GETMAXCOMMODE_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
    if(ComMode == NULL_PTR)
    {
      /* DET entry */
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETMAXCOMMODE_ID);
      retValue = E_NOT_OK;
    }
    else
    {
      if(User < ComM_MaxNumberOfUsers) /* User handle is valid */
      {
#endif
        *ComMode = (ComM_ModeType)COMM_FULL_COMMUNICATION;
       
        for(iByteMaskIndex = ComM_UserByteMaskIndex[User]; iByteMaskIndex < ComM_UserByteMaskIndex[User+1]; iByteMaskIndex++)
        {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
          if((ComM_IdentityMapping[ComM_UserByteMask[iByteMaskIndex].Channel] & ComM_ActiveIdentityMask) != 0u)
          {
            bUserActive = TRUE;
#endif
            /* PRQA S 3415 1 */ /* MD_ComM_3415 */
            if( (ComM_NoComLimitationActive(ComM_UserByteMask[iByteMaskIndex].Channel) == TRUE) ||
                (ComM_PreventWakeUpActive(ComM_UserByteMask[iByteMaskIndex].Channel) == TRUE) )
            {
              *ComMode = (ComM_ModeType)COMM_NO_COMMUNICATION;
            }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
          }
#endif
        }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
        if(bUserActive == FALSE)
        {
          *ComMode = (ComM_ModeType)COMM_NO_COMMUNICATION;
        }
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
      }
      else
      {
        /* DET entry */
        ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETMAXCOMMODE_ID);
        retValue = E_NOT_OK;
      }
    }
  }

  return retValue;
#else
  return E_OK;
#endif

} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/*********************************************************************************************************************
  FUNCTION: ComM_GetRequestedComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: ComM_UserHandleType     User                    user handle
          ComM_ModeType           *ComMode                communication mode
  Output: ComM_ModeType           *ComMode                communication mode
  Return: Std_ReturnType                                  return value of ComM API
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to query the currently highest requested communication mode of the corresponding user.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_GetRequestedComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode)
{
  uint8 iByteMaskIndex;
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  boolean bUserActive;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;
#endif

#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  bUserActive = FALSE;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  ComM_CheckInitStatus(COMM_GETREQUESTEDCOMMODE_ID, COMM_E_NOT_INITED, retValue)  /* check the initialization state of the ComM */
  
  if(retValue == E_OK)
  {
    if(ComMode == NULL_PTR)
    {
      /* DET entry */
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETREQUESTEDCOMMODE_ID);
      retValue = E_NOT_OK;
    }
    else
    {
      if(User < ComM_MaxNumberOfUsers) /* check of valid user handle */
      {
#endif

        SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);

        *ComMode = (ComM_ModeType)COMM_FULL_COMMUNICATION;

        for(iByteMaskIndex = ComM_UserByteMaskIndex[User]; iByteMaskIndex < ComM_UserByteMaskIndex[User+1]; iByteMaskIndex++)
        {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
          if((ComM_IdentityMapping[ComM_UserByteMask[iByteMaskIndex].Channel] & ComM_ActiveIdentityMask) != 0u)
          {
            bUserActive = TRUE;
#endif
            if( (ComM_UserReqFullComArray[ComM_UserByteMask[iByteMaskIndex].ByteIndex] & ComM_UserByteMask[iByteMaskIndex].SetMask) > 0x00)
            {
              /* nothing to do the requested mode is COMM_FULL_COMMUNCIATION */
            }
            else
            {
              /* minimum one channel is not requested the requested mode is now COMM_NO_COMMUNCIATION */
              *ComMode = (ComM_ModeType)COMM_NO_COMMUNICATION;
            }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
          }
#endif
        }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
        if(bUserActive == FALSE)
        {
          *ComMode = (ComM_ModeType)COMM_NO_COMMUNICATION;
        }
#endif

        SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
      }
      else
      {
        retValue = E_NOT_OK;
        ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETREQUESTEDCOMMODE_ID);
      }
    }
  }

  return retValue;
#else
  return E_OK;
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/*********************************************************************************************************************
  FUNCTION: ComM_GetCurrentComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: ComM_UserHandleType     User                    user handle
          ComM_ModeType           *ComMode                communication mode
  Output: ComM_ModeType           *ComMode                communication mode
  Return: Std_ReturnType                                  return value of ComM API
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to query the current communication mode of the corresponding user.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurrentComMode(ComM_UserHandleType User, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComMode)
{
  uint8 iByteMaskIndex;
  ComM_ModeType tmpComMode;
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  boolean bUserActive;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;
#endif

#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  bUserActive = FALSE;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  ComM_CheckInitStatus(COMM_GETCURRENTCOMMODE_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
    if(ComMode == NULL_PTR)
    {
      /* DET entry */
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETCURRENTCOMMODE_ID);
      retValue = E_NOT_OK;
    }
    else
    {
      if(User < ComM_MaxNumberOfUsers)
      {
#endif
        SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);
        /* get current mode of the BusSM */

        *ComMode = COMM_FULL_COMMUNICATION;
        for(iByteMaskIndex = ComM_UserByteMaskIndex[User]; iByteMaskIndex < ComM_UserByteMaskIndex[User+1]; iByteMaskIndex++)
        {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
          if((ComM_IdentityMapping[ComM_UserByteMask[iByteMaskIndex].Channel] & ComM_ActiveIdentityMask) != 0u)
          {
            bUserActive = TRUE;
#endif
            ComM_GetCurrentBusSMMode(ComM_UserByteMask[iByteMaskIndex].Channel, &tmpComMode);
            if(tmpComMode < *ComMode)
            {
              *ComMode = tmpComMode;
            }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
          }
#endif
        }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
        if(bUserActive == FALSE)
        {
          *ComMode = COMM_NO_COMMUNICATION;
        }
#endif
        SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
      }
      else
      {
        retValue = E_NOT_OK;
        ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETCURRENTCOMMODE_ID);
      }
    }
  }

  return retValue;
#else
  return E_OK;
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/*********************************************************************************************************************
  FUNCTION: ComM_GetInhibitionStatus
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType    Channel                 channel handle
          ComM_InhibitionStatusType *Status                 inhibition status imformation
  Output: ComM_InhibitionStatusType *Status                 inhibition status imformation
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to get the inhibition status.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_GetInhibitionStatus( NetworkHandleType Channel, P2VAR(ComM_InhibitionStatusType, AUTOMATIC, COMM_APPL_VAR) Status)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_GETINHIBITIONSTATUS_ID, COMM_E_NOT_INITED, retValue)

#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
  if((ComM_IdentityMapping[Channel] & ComM_ActiveIdentityMask) == 0u)
  {
    ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETINHIBITIONSTATUS_ID);
  }
#endif
  
  if(retValue == E_OK)
  {
    if(Status == NULL_PTR)
    {
      /* DET entry */
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETINHIBITIONSTATUS_ID);
      retValue = E_NOT_OK;
    }
    else
    {
#endif
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[Channel] & ComM_ActiveIdentityMask) != 0u)
      {
#endif
        *Status = ComM_Inhibition.ComM_InhibitionStatus[Channel];
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
      else
      {
        *Status = 0u;
      }
#endif
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
    }
  }

  return retValue;
#else
  return E_OK;
#endif
}


/*********************************************************************************************************************
  FUNCTION: ComM_PreventWakeUp
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType         Channel                 channel handle
          boolean                   Status                  prevent wake up state
  Output: -
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to set the inhibition status for to COMM_NO_WAKEUP.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_PreventWakeUp( NetworkHandleType Channel, boolean Status)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_PREVENTWAKEUP_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
    if(Channel >= ComM_Active_Channel)
    {
      /* DET entry */
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_PREVENTWAKEUP_ID);
      retValue = E_NOT_OK;
    }
    else
    {
#endif

#if (COMM_MODE_LIMITATION == STD_ON) /* ESCAN00054786 */
# if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[Channel] & ComM_ActiveIdentityMask) != 0u)
      {
# endif
        SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);

        if(Status == TRUE)
        {
          ComM_Inhibition.ComM_InhibitionStatus[Channel] |= (uint8)0x01;
        }
        else
        {
          ComM_Inhibition.ComM_InhibitionStatus[Channel] &= (uint8)0xFE;
        }

        /* store non-volatile values */
        ComM_StoreNonVolatileValues();

        SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);
# if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
# endif
#else
  ComM_DummyStatement( Status ) /* PRQA S 3112 */ /* MD_ComM_3112 */
#endif
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
    }
  }

  return retValue;
#else
# if (COMM_MODE_LIMITATION == STD_OFF)
  ComM_DummyStatement( Channel ) /* PRQA S 3112 */ /* MD_ComM_3112 */
# endif

  return E_OK;
#endif
}


/*********************************************************************************************************************
  FUNCTION: ComM_LimitChannelToNoComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType    Channel                 channel handle
          boolean                   Status                  prevent wake up state
  Output: -
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to set the inhibition to no communication.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode( NetworkHandleType Channel, boolean Status)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_LIMITCHANNELTONOCOMMODE_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
    if(Channel >= ComM_Active_Channel)
    {
      /* DET entry */
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_LIMITCHANNELTONOCOMMODE_ID);
      retValue = E_NOT_OK;
    }
    else
    {
#endif

#if (COMM_MODE_LIMITATION == STD_ON) /* ESCAN00054786 */
# if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[Channel] & ComM_ActiveIdentityMask) != 0u)
      {
# endif
        SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);

        if(Status == TRUE)
        {
          if(ComM_ActiveComMode[Channel] == COMM_NETWORK_REQUESTED)
          {
            ComM_Inhibition.ComM_InhibitionStatus[Channel] |= (uint8)0x02;
          }
        }
        else
        {
          ComM_Inhibition.ComM_InhibitionStatus[Channel] &= (uint8)0xFD;
        }
        SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);
# if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
# endif
#else
  ComM_DummyStatement( Status ) /* PRQA S 3112 */ /* MD_ComM_3112 */
#endif
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
    }
  }

  return retValue;
#else
# if (COMM_MODE_LIMITATION == STD_OFF)
  ComM_DummyStatement( Channel ) /* PRQA S 3112 */ /* MD_ComM_3112 */
# endif

  return E_OK;
#endif
}


/*********************************************************************************************************************
  FUNCTION: ComM_LimitECUToNoComMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: boolean                   Status                  prevent wake up state
  Output: -
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to limit the ECU to no communication mode.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode(boolean Status)
{
  uint8          ComM_Channel;

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_LIMITECUTONOCOMMODE_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
#endif
    for(ComM_Channel=0; ComM_Channel < ComM_Active_Channel; ComM_Channel++)
    {
      (void)ComM_LimitChannelToNoComMode((NetworkHandleType)ComM_Channel, Status);
    }
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  }

  return retValue;
#else
  return E_OK;
#endif
}

/*********************************************************************************************************************
  FUNCTION: ComM_ReadInhibitCounter
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: uint16                    CounterValue            counter of the rejected full com modes
  Output: uint16                    CounterValue            counter of the rejected full com modes
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to get how often the full communication mode was limited.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter(P2VAR(uint16, AUTOMATIC, COMM_APPL_VAR) CounterValue)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_READINHIBITCOUNTER_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
    if(CounterValue == NULL_PTR)
    {
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_READINHIBITCOUNTER_ID);
      retValue = E_NOT_OK;
    }
    else
    {
#endif
      *CounterValue = ComM_Inhibition.ComM_InhibitCnt;

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
    }
  }

  return retValue;
#else
  return E_OK;
#endif
}

/*********************************************************************************************************************
  FUNCTION: ComM_ResetInhibitCounter
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to reset the full communication mode inhibit counter.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter(void)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_RESETINHIBITCOUNTER_ID, COMM_E_NOT_INITED, retValue)

  if(retValue == E_OK)
#endif
  {

    ComM_Inhibition.ComM_InhibitCnt = (uint16)0x00;

    /* store non-volatile values */
    ComM_StoreNonVolatileValues();
  }

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  return retValue;
#else
  return E_OK;
#endif
}


/*********************************************************************************************************************
  FUNCTION: ComM_SetECUGroupClassification
----------------------------------------------------------------------------------------------------------------------
  API     Type                      Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: ComM_InhibitionStatusType Status                  ECU grou calssification
  Output: -
  Return: Std_ReturnType
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition: ComM must be initialized via the function ComM_Init

  Function to set the ECu group classification.
*********************************************************************************************************************/
FUNC(Std_ReturnType, COMM_CODE) ComM_SetECUGroupClassification(ComM_InhibitionStatusType Status)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue;

  retValue = E_OK;

  ComM_CheckInitStatus(COMM_SETECUGROUPCLASSIFICATION_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
  {
    if(Status > 3)
    {
      ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_SETECUGROUPCLASSIFICATION_ID);
      retValue = E_NOT_OK;
    }
    else
#endif
    {
      ComM_Inhibition.ComM_ECUGroupClassification = Status;
      /* store non-volatile values */
      ComM_StoreNonVolatileValues();
    }

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  }

  return retValue;
#else
  return E_OK;
#endif
}


#if (COMM_VERSION_INFO_API == STD_ON)
/*********************************************************************************************************************
  FUNCTION: ComM_GetVersionInfo
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: Std_VersionInfo         *versionInfo            version information
  Output: Std_VersionInfo         *versionInfo            version information
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: upper layer
  Precondition:

  Function to get the component version information.
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COMM_APPL_VAR) versioninfo)
{
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  if(versioninfo == NULL_PTR)
  {
    ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_GETVERSIONINFO_ID);
  }
  else
#endif
  {
    versioninfo->vendorID = COMM_VENDOR_ID;
    versioninfo->moduleID = COMM_MODULE_ID;
    versioninfo->sw_major_version = COMM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = COMM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = COMM_SW_PATCH_VERSION; 
  }

}
#endif

#if ( COMM_PNC_SUPPORT == STD_ON )
/*********************************************************************************************************************
  FUNCTION: ComM_DisablePNActivationState
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: Application
  Precondition: ComM must be initialized via the function ComM_Init

  API to disable PNC functionality at runtime during BSW initialization
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_DisablePNActivationState(void)
{
  /* ESCAN00066498 */
# if ( COMM_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retValue = E_OK;

  ComM_CheckInitStatus(COMM_DISABLEPNACTIVATIONSTATE_ID, COMM_E_NOT_INITED, retValue)
  
  if(retValue == E_OK)
# endif
  {
    /* The same variable is also used in configuration variant PostBuild */
    ComM_PncEnabled = FALSE;
  }

  return;
}
#endif

/*********************************************************************************************************************
  FUNCTION: ComM_MainFunction
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                  channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: ComM_MainTaskFunction_<channel_number>
  Precondition: ComM must be initialized via the function ComM_Init

  Main function of the communication manager.
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_MainFunction(NetworkHandleType Channel)
{
  ComM_SubModeType       highestComModeReq;     /* highest ComM mode request */
  uint8                  calculatedComModeReq;  /* the calculated ComM mode */
  EcuM_StateType         EcuM_State;            /* EcuM RUN mode state */

#if (COMM_PNC_SUPPORT == STD_ON)
  uint8 pncIndex;
#endif

#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  if( Channel < ComM_Active_Channel)
#endif
  {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
    if((ComM_IdentityMapping[Channel] & ComM_ActiveIdentityMask) != 0u)
    {
#endif
      SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_1);

      /* get highest user request for current channel */
      highestComModeReq     = ComM_CalculateHighestComMode(Channel);

      if(ComM_BusComModeReq[Channel] > highestComModeReq) /* bus request is highest request */
      {
        highestComModeReq = ComM_BusComModeReq[Channel];
      }
 
      if( (ComM_ActiveComMode[Channel] == COMM_NO_COM) && (highestComModeReq > COMM_NO_COM) )
      {
        /* ComM is in Mode NO COMMUNICATION and a request for a higher ComM mode is pending */
        
        /* ESCAN00055590: once communication requested, ComM shall not trigger shutdown on channels with Nm variant NONE */
        if(ComM_Nm_Type[Channel] == NM_VARIANT_NONE)
        {
          ComM_BusComModeReq[Channel] = COMM_NETWORK_REQUESTED;
        }

        /* check if the ComM run mode request was set, to avoid multiple run mode requests */
        if(EcuM_ComM_HasRequestedRUN(Channel) == FALSE)
        {
          /* no ComM run mode request is set,
           * request ComM run mode
           */
          if(EcuM_ComM_RequestRUN(Channel) == E_NOT_OK)
          {
            /* DET error entry, that the EcuM RUN mode request failed */
            ComM_Assert(COMM_E_ERROR_IN_PROV_SERVICE, COMM_MAINFUNCTION_ID);
          }
        }
      }

      /* check EcuM state */
      (void)EcuM_GetState(&EcuM_State);
      if( EcuM_State == ECUM_STATE_APP_RUN )
      {
        /* EcuM is in mode RUN */
        do
        {
          if( ((ComM_ActiveComMode[Channel] == COMM_READY_TO_SLEEP) || (ComM_ActiveComMode[Channel] == COMM_NETWORK_REQUESTED)) &&
              ((ComM_MinFullComModeTime[Channel] > 0x00) || (ComM_NmLightTimeout[Channel] > 0x00)) &&
              (highestComModeReq != COMM_NETWORK_REQUESTED) )
          {
            /* Stay in the current state and ignore the highestComModeReq if
             * - channel is in COMM_FULL_COMMUNICATION mode and either Min Full Comm or Nm LIGHT timer is running
             * - but do not ignore COMM_FULL_COMMUNICATION requests by users or Dcm.
             * Example: channel is in COMM_READY_TO_SLEEP, Nm LIGHT timer is running and user (or Dcm) requests
             * COMM_FULL_COMMUNICATION. According to ComM479 channel shall immediately switch to COMM_NETWORK_REQUESTED
             * and cancel Nm LIGHT timer (ESCAN00061242).
             */
            highestComModeReq = ComM_ActiveComMode[Channel];
          }
          else
          {
            /* calculate the next transition step */
            calculatedComModeReq  = ComM_TransitionTable[highestComModeReq][ComM_ActiveComMode[Channel]];
            if(calculatedComModeReq != NO_TRANSMI) /* check if a transition is necessary */
            {
              ComM_TransitionFctTable[calculatedComModeReq][ComM_ActiveComMode[Channel]](Channel);

              /* check if transition has performed */
              ComM_ActiveComMode[Channel] = (ComM_SubModeType)calculatedComModeReq; /* update the ComM state transition */
            }
            else /* transtion is not necessary */
            {
              highestComModeReq = ComM_ActiveComMode[Channel];
            }
          }
        }while(ComM_ActiveComMode[Channel] != highestComModeReq);

#if (COMM_PNC_SUPPORT == STD_ON)
        if(ComM_PncEnabled == TRUE)
        {
          /* Handle PNC Prepare Sleep Timer in context of the channel 0 because the initial timer value ComM_PncPSTimer
           * is calculated based on the cycle time of channel 0. The same initial value is used for all PNCs. */
          if(Channel == 0)
          {
            for(pncIndex = 0; pncIndex < ComM_PncCount; pncIndex++)
            {
              if( (ComM_ActivePncComMode[pncIndex] == COMM_PNC_PREPARE_SLEEP) && (ComM_PncPSleepTimer[pncIndex] > 0) )
              {
                ComM_PncPSleepTimer[pncIndex]--;
                if( (ComM_BusPncComModeReq[pncIndex] == COMM_PNC_PREPARE_SLEEP) && (ComM_PncPSleepTimer[pncIndex] == 0) )
                {
                  ComM_BusPncComModeReq[pncIndex] = COMM_PNC_NO_COMMUNICATION;
                }
              }
            }
          }

          /* Consider only channels with at least one PNC assigned (ESCAN00073286) */
          if( ComM_ChannelHasPnc[Channel] == TRUE )
          {
            ComM_PNModeArbitration(Channel);
          }
        }
#endif

        /* Notify users/RTE about new mode. Do it outside of the exclusive area to avoid that calls to 
         * application or RTE extend the interrupt lock time. */

        if( ComM_StateChange[Channel] != COMM_NO_STATE_CHANGE )
        {
          /* Channel users: BusSM indicated a state change or the last mode notification failed */
          SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_1);
          ComM_StateChangeNotification(Channel);
          SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_1);
        }

#if (COMM_PNC_SUPPORT == STD_ON)
        if( ComM_NotifyPncStateChange == TRUE )
        {
          /* PNC users: a PNC changed the state from FULL_COM to NO_COM or vice versa or the last mode notification failed (ESCAN00066776) */
          SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_1);
          if( ComM_PncStateChangeNotification() == E_OK )
          {
            /* All PNC users have been succesfully notified about new mode, reset the flag.
             * Otherwise, if at least one user mode notification failed, ComM will try again in the next task. */
            ComM_NotifyPncStateChange = FALSE;
          }
          SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_1);
        }
#endif

        if( (ComM_ActiveComMode[Channel] == COMM_NO_COM) && (highestComModeReq == COMM_NO_COM) && (ComM_BusSmState[Channel] == COMM_NO_COMMUNICATION) )
        {
          /* ComM is in state NO COMMUNCIATION and no request for a higher ComM mode os pending */
          if(EcuM_ComM_HasRequestedRUN(Channel) == TRUE)
          {
            /* release the ComM channel run mode request */
            if(EcuM_ComM_ReleaseRUN(Channel) == E_NOT_OK)
            {
             ComM_Assert(COMM_E_ERROR_IN_PROV_SERVICE, COMM_MAINFUNCTION_ID);
            }
          }
        }

        if(ComM_MinFullComModeTime[Channel] > 0x00)
        {
          /* Minimum FULL mode duration is supported by Nm variants OSEK and LIGHT, but not by NONE (related to ESCAN00055590, ESCAN00058046) */
          ComM_MinFullComModeTime[Channel]--;
          if( (ComM_MinFullComModeTime[Channel] == 0x00) && (ComM_NmLightTimeout[Channel] == 0x00))
          {
            if(ComM_Nm_Type[Channel] == NM_VARIANT_OSEK)
            {
              ComM_BusComModeReq[Channel] = COMM_READY_TO_SLEEP;
            }
            else
            {
              /* Nm variant LIGHT: no shutdown synchronization with means of a timeout if ComMNmLightTimeout is configured with 0x00.
              In this case the sub-state COMM_READY_TO_SLEEP is omitted and channel shall enter COMM_NO_COM. ESCANXXXXXXXX */
              ComM_BusComModeReq[Channel] = NO_COM;
            }
          }
        }

        if((ComM_NmLightTimeout[Channel] > 0x00) && (ComM_MinFullComModeTime[Channel] == 0x00))
        {
          /* Nm variant LIGHT: shutdown synchronization with means of a timeout */
          ComM_NmLightTimeout[Channel]--;

          if(ComM_NmLightTimeout[Channel] == 0x00)
          {
            ComM_BusComModeReq[Channel] = NO_COM;
          }
        }
      }

      SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_1);
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
   }
#endif


  } /* if( Channel < ComM_Active_Channel) */
#if ( COMM_DEV_ERROR_DETECT == STD_ON )
  else
  {
    ComM_Assert(COMM_E_WRONG_PARAMETERS, COMM_MAINFUNCTION_ID);
  }
#endif
} /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

#if (COMM_PNC_SUPPORT == STD_ON)
/*********************************************************************************************************************
  FUNCTION: ComM_PNModeArbitration
----------------------------------------------------------------------------------------------------------------------
  API     Type                     Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                  channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: 
  Precondition: 

  
*********************************************************************************************************************/
STATIC FUNC(void, COMM_CODE) ComM_PNModeArbitration(NetworkHandleType Channel)
{
  uint8 ComM_CurrentPn;
  ComM_PncModeType highestComModeReq;
  boolean bPncHandled;
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
  NetworkHandleType ComM_PncChIdx;
  ComM_SubModeType ComM_ActiveComModeTmp;
#endif

  for(ComM_CurrentPn = 0; ComM_CurrentPn < ComM_PncCount; ComM_CurrentPn++)
  {
    highestComModeReq = COMM_PNC_NO_COMMUNICATION;
    bPncHandled = FALSE;

#if (COMM_PNC_ACTIVE_COORD == STD_ON)
    ComM_ActiveComModeTmp = COMM_NETWORK_REQUESTED;
    for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
    {
      if(ComM_PncChannelMapping[ComM_PncChIdx] == Channel)
      {
        /* Current PN iterator shall be handled because assigned to the channel the function is called for */
        bPncHandled = TRUE;
      }

# if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[ComM_PncChannelMapping[ComM_PncChIdx]] & ComM_ActiveIdentityMask) != 0u)
      {
# endif
        if( ComM_ActiveComMode[ComM_PncChannelMapping[ComM_PncChIdx]] < ComM_ActiveComModeTmp)
        {
          /* Calculate the lowest active communication mode of all channels asigned to the PNC */
          ComM_ActiveComModeTmp = ComM_ActiveComMode[ComM_PncChannelMapping[ComM_PncChIdx]];
        }
# if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
# endif
    }
#else
    if(ComM_PncChMap[ComM_CurrentPn] == Channel)
    {
      bPncHandled = TRUE;
    }
#endif

    if(bPncHandled == TRUE)
    {
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
      if(ComM_ActiveComModeTmp > COMM_SI_COM)
      {
        /* highestComModeReq shall be COMM_PNC_NO_COMMUNICATION (default) as long as at least one channel is not in FULL_COMM yet.
        This is to ensure that a state transition (activation) of a coordinated PNC is performed AFTER all assigned channels have entered FULL_COMM. */
#endif
        highestComModeReq = ComM_CalculateHighestPNComMode(ComM_CurrentPn, Channel);
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
      }
#endif
    }

    if( (bPncHandled == TRUE) && (highestComModeReq != ComM_ActivePncComMode[ComM_CurrentPn]) )
    {
      switch(ComM_ActivePncComMode[ComM_CurrentPn])
      {
        case COMM_PNC_NO_COMMUNICATION:
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
          if(highestComModeReq == COMM_PNC_REQUESTED_PASSIVE)
          {
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_REQUESTED_PASSIVE, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ALL_SIG);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED_PASSIVE;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_REQUESTED);
            ComM_NotifyPncStateChange = TRUE;
          }
          else if(highestComModeReq == COMM_PNC_REQUESTED)
          {
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ACTIVE_SIG_ONLY);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( (ComM_PncGwType[ComM_PncChannelMapping[ComM_PncChIdx]] == COMM_GATEWAY_TYPE_ACTIVE) &&
                  (ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE) )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
#else
          if(highestComModeReq == COMM_PNC_REQUESTED)
          {
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_OFF */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ALL_SIG);
            if( ComM_PncNmRequest[ComM_PncChMap[ComM_CurrentPn]] == TRUE )
            {
              (void)Nm_NetworkRequest(ComM_PncChMap[ComM_CurrentPn]);
            }
#endif
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_REQUESTED, common part disregarding coordination type */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_REQUESTED);
            ComM_NotifyPncStateChange = TRUE;
          }
          else if(highestComModeReq == COMM_PNC_READY_SLEEP)
          {
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_READY_SLEEP */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_READY_SLEEP;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
            ComM_NotifyPncStateChange = TRUE;
          }
          else if(highestComModeReq == COMM_PNC_PREPARE_SLEEP)
          {
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_PREPARE_SLEEP */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_PREPARE_SLEEP;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_PREPARE_SLEEP);
            ComM_PncPSleepTimer[ComM_CurrentPn] = ComM_PncPSTimer;
            ComM_NotifyPncStateChange = TRUE;
          }
          else
          {
            /* Nothing to do as all specified values of highestComModeReq have been handled. Statement is needed for MISRA-C:2004 compliance (Rule 14.10). */
          }
          break;
        case COMM_PNC_PREPARE_SLEEP:
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
          if(highestComModeReq == COMM_PNC_REQUESTED_PASSIVE)
          {
            /* COMM_PNC_PREPARE_SLEEP -> COMM_PNC_REQUESTED_PASSIVE, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ALL_SIG);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED_PASSIVE;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_REQUESTED);
          }
          else if(highestComModeReq == COMM_PNC_REQUESTED)
          {
            /* COMM_PNC_PREPARE_SLEEP -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ACTIVE_SIG_ONLY);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( (ComM_PncGwType[ComM_PncChannelMapping[ComM_PncChIdx]] == COMM_GATEWAY_TYPE_ACTIVE) &&
                  (ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE) )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
#else
          if(highestComModeReq == COMM_PNC_REQUESTED)
          {
            /* COMM_PNC_PREPARE_SLEEP -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_OFF */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ALL_SIG);
            if( ComM_PncNmRequest[ComM_PncChMap[ComM_CurrentPn]] == TRUE )
            {
              (void)Nm_NetworkRequest(ComM_PncChMap[ComM_CurrentPn]);
            }
#endif
            /* COMM_PNC_NO_COMMUNICATION -> COMM_PNC_REQUESTED, common part disregarding coordination type */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_REQUESTED);
          }
          else if(highestComModeReq == COMM_PNC_READY_SLEEP)
          {
            /* COMM_PNC_PREPARE_SLEEP -> COMM_PNC_READY_SLEEP */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_READY_SLEEP;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
          }
          else if(highestComModeReq == COMM_PNC_NO_COMMUNICATION)
          {
            /* COMM_PNC_PREPARE_SLEEP -> COMM_PNC_NO_COMMUNICATION */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_NO_COMMUNICATION;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_NO_COMMUNICATION);
            ComM_NotifyPncStateChange = TRUE;
          }
          else
          {
            /* Nothing to do as all specified values of highestComModeReq have been handled. Statement is needed for MISRA-C:2004 compliance (Rule 14.10). */
          }

          /* When leaving COMM_PNC_PREPARE_SLEEP state, always stop the timer and reset ComM_BusPncComModeReq[] 
          if no EIRA = 1 signal received for the PNC. Needed e.g. in case PNC is not considered by Nm filter mask.
          Possible scenario: Synchronous Wake-up, FULL_COM request, NO_COM request. In this case highestComModeReq 
          shall be COMM_PNC_NO_COMMUNICATION and PNC shall enter COMM_PNC_PREPARE_SLEEP. (ESCAN00060977) */
          ComM_PncPSleepTimer[ComM_CurrentPn] = 0;
          if(ComM_BusPncComModeReq[ComM_CurrentPn] == COMM_PNC_PREPARE_SLEEP)
          {
            ComM_BusPncComModeReq[ComM_CurrentPn] = COMM_PNC_NO_COMMUNICATION;
          }

          break;
        case COMM_PNC_READY_SLEEP:
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
          if(highestComModeReq == COMM_PNC_REQUESTED_PASSIVE)
          {
            /* COMM_PNC_READY_SLEEP -> COMM_PNC_REQUESTED_PASSIVE, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ALL_SIG);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED_PASSIVE;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_REQUESTED);
          }
          else if(highestComModeReq == COMM_PNC_REQUESTED)
          {
            /* COMM_PNC_READY_SLEEP -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ACTIVE_SIG_ONLY);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( (ComM_PncGwType[ComM_PncChannelMapping[ComM_PncChIdx]] == COMM_GATEWAY_TYPE_ACTIVE) &&
                  (ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE) )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
#else
          if(highestComModeReq == COMM_PNC_REQUESTED)
          {
            /* COMM_PNC_READY_SLEEP -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_OFF */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_ALL_SIG);
            if( ComM_PncNmRequest[ComM_PncChMap[ComM_CurrentPn]] == TRUE )
            {
              (void)Nm_NetworkRequest(ComM_PncChMap[ComM_CurrentPn]);
            }
#endif
            /* COMM_PNC_READY_SLEEP -> COMM_PNC_REQUESTED, common part disregarding coordination type */
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_REQUESTED);
          }
          else if( highestComModeReq == COMM_PNC_NO_COMMUNICATION )
          {
            /* Always indicate COMM_PNC_PREPARE_SLEEP to BswM, even if the state is omitted in case ComM_PncPSTimer == 0. */
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_PREPARE_SLEEP);
            
            if( ComM_PncPSTimer > 0 )
            {
              /* COMM_PNC_READY_SLEEP -> COMM_PNC_PREPARE_SLEEP */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_PREPARE_SLEEP;
              ComM_PncPSleepTimer[ComM_CurrentPn] = ComM_PncPSTimer;
            }
            else
            {
              /* Special case if ComM_PncPSTimer == 0: COMM_PNC_READY_SLEEP -> COMM_PNC_NO_COMMUNICATION */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_NO_COMMUNICATION;
              BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_NO_COMMUNICATION);
              ComM_NotifyPncStateChange = TRUE;
            }
          }
          else
          {
            /* Nothing to do as all possible highestComModeReq have been handled. Statement is needed for MISRA-C:2004 compliance (Rule 14.10). */
          }
          break;
        case COMM_PNC_REQUESTED:
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
          if(highestComModeReq == COMM_PNC_REQUESTED_PASSIVE)
          {
            /* COMM_PNC_REQUESTED -> COMM_PNC_REQUESTED_PASSIVE, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, TRUE, COMM_SEND_PASSIVE_SIG_ONLY);
            for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_CurrentPn]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_CurrentPn+1]; ComM_PncChIdx++)
            {
              if( (ComM_PncGwType[ComM_PncChannelMapping[ComM_PncChIdx]] == COMM_GATEWAY_TYPE_PASSIVE) &&
                  (ComM_PncNmRequest[ComM_PncChannelMapping[ComM_PncChIdx]] == TRUE) )
              {
                (void)Nm_NetworkRequest(ComM_PncChannelMapping[ComM_PncChIdx]);
              }
            }
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED_PASSIVE;
          }
          else if( highestComModeReq == COMM_PNC_READY_SLEEP )
          {
            /* COMM_PNC_REQUESTED -> COMM_PNC_READY_SLEEP, if COMM_PNC_ACTIVE_COORD == STD_ON.*/
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_ACTIVE_SIG_ONLY);
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_READY_SLEEP;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
          }
          else
          {
            /* Special case: highestComModeReq == COMM_PNC_NO_COMMUNICATION, i.e. no EIRA received for the PNC because 
            it is not considered by Nm filter mask (ESCAN00060977) */
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_ACTIVE_SIG_ONLY);
            /* Always indicate COMM_PNC_READY_SLEEP and COMM_PNC_PREPARE_SLEEP to BswM, even if the states are omitted effectively. */
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_PREPARE_SLEEP);

            if( ComM_PncPSTimer > 0 )
            {
              /* COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_PREPARE_SLEEP */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_PREPARE_SLEEP;
              ComM_PncPSleepTimer[ComM_CurrentPn] = ComM_PncPSTimer;
            }
            else
            {
              /* Special case if ComM_PncPSTimer == 0: COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_NO_COMMUNICATION */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_NO_COMMUNICATION;
              BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_NO_COMMUNICATION);
              ComM_NotifyPncStateChange = TRUE;
            }
          }
#else
          if( highestComModeReq == COMM_PNC_READY_SLEEP )
          {
            /* COMM_PNC_REQUESTED -> COMM_PNC_READY_SLEEP, if COMM_PNC_ACTIVE_COORD == STD_OFF */
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_ALL_SIG);
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_READY_SLEEP;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
          }
          else 
          {
            /* Special case: highestComModeReq == COMM_PNC_NO_COMMUNICATION, i.e. no EIRA received for the PNC because 
            it is not considered by Nm filter mask (ESCAN00060977) */
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_ALL_SIG);
            /* Always indicate COMM_PNC_READY_SLEEP and COMM_PNC_PREPARE_SLEEP to BswM, even if the states are omitted effectively. */
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_PREPARE_SLEEP);

            if( ComM_PncPSTimer > 0 )
            {
              /* COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_PREPARE_SLEEP */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_PREPARE_SLEEP;
              ComM_PncPSleepTimer[ComM_CurrentPn] = ComM_PncPSTimer;
            }
            else
            {
              /* Special case if ComM_PncPSTimer == 0: COMM_PNC_REQUESTED -> COMM_PNC_NO_COMMUNICATION */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_NO_COMMUNICATION;
              BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_NO_COMMUNICATION);
              ComM_NotifyPncStateChange = TRUE;
            }
          }
#endif
          break;
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
        case COMM_PNC_REQUESTED_PASSIVE:
          if( highestComModeReq == COMM_PNC_REQUESTED )
          {
            /* COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_REQUESTED, if COMM_PNC_ACTIVE_COORD == STD_ON */
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_PASSIVE_SIG_ONLY);
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_REQUESTED;
          }
          else if( highestComModeReq == COMM_PNC_READY_SLEEP )
          {
            /* COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_READY_SLEEP, if COMM_PNC_ACTIVE_COORD == STD_ON. */
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_ALL_SIG);
            ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_READY_SLEEP;
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
          }
          else 
          {
            /* Special case: highestComModeReq == COMM_PNC_PREPARE_SLEEP, i.e. no EIRA received for the PNC because 
            it is not considered by Nm filter mask (ESCAN00060977) */
            ComM_ComSendSignal(ComM_CurrentPn, FALSE, COMM_SEND_ALL_SIG);
            /* Always indicate COMM_PNC_READY_SLEEP and COMM_PNC_PREPARE_SLEEP to BswM, even if the states are omitted effectively. */
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_READY_SLEEP);
            BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_PREPARE_SLEEP);

            if( ComM_PncPSTimer > 0 )
            {
              /* COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_PREPARE_SLEEP */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_PREPARE_SLEEP;
              ComM_PncPSleepTimer[ComM_CurrentPn] = ComM_PncPSTimer;
            }
            else
            {
              /* Special case if ComM_PncPSTimer == 0: COMM_PNC_REQUESTED_PASSIVE -> COMM_PNC_NO_COMMUNICATION */
              ComM_ActivePncComMode[ComM_CurrentPn] = COMM_PNC_NO_COMMUNICATION;
              BswM_ComM_CurrentPNCMode(ComM_PncInfoMask[ComM_CurrentPn].PncId, COMM_PNC_NO_COMMUNICATION);
              ComM_NotifyPncStateChange = TRUE;
            }
          }
          break;
#endif
        default: /* nothing to do */
          break;
      }
    } /* PNC state transition */
  } /* Iteration over PNCs */
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
 FUNCTION:ComM_CalculateHighestComMode
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                 channel handle
  Output: -                       -                       -
  Return: ComM_SubModeType        -                       the current highest communciation mode

-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: ComM function ComM_MainFunction
  Precondition: -

  This fucntion calculates the current highest communication mode request
**********************************************************************************************************************/
STATIC FUNC( ComM_SubModeType, COMM_CODE) ComM_CalculateHighestComMode( NetworkHandleType  Channel )
{
  ComM_SubModeType lHighestRequest;
  uint8         lStartIndex;
  uint8         lStopIndex;
#if (COMM_PNC_SUPPORT == STD_ON)
  uint8         ComM_PnIdx;
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
  NetworkHandleType ComM_PncChIdx;
  uint8         userIndex;
  uint8         iByteMaskIndex;
  ComM_PncModeType highestPNComModeReq = COMM_PNC_NO_COMMUNICATION;
  ComM_PncModeType tmpPNComModeReq;
# endif
#endif

  lHighestRequest = COMM_NO_COM; /* default value is no communication */
  lStartIndex = (NetworkHandleType)0x00;

  SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);
  if(Channel > 0x00) 
  {
    /* get the start index of the ComM user bit field */
    lStartIndex = (uint8)((uint8)(ComM_ChannelStopIndex[(Channel - 0x01)]) + (uint8)0x01);
  }

  /* Iterate over the user request bit field ComM_UserReqFullComArray[] for the given ComM channel. */
  /* PRQA S 2462,3689 1 */ /* MD_ComM_2462,MD_ComM_3689 */
  for(lStopIndex = ComM_ChannelStopIndex[Channel];lStartIndex <= lStopIndex;lStartIndex++)
  {
    if(ComM_UserReqFullComArray[lStartIndex] > 0x00) /* full request is set */
    {
#if (COMM_PNC_SUPPORT == STD_ON)
      if( (ComM_PncEnabled == TRUE) && (ComM_ChannelHasPnc[Channel] == TRUE) ) /* Consider only channels with at least one PNC assigned (ESCAN00073286) */
      {
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
        /* Case 1.1 - PNC coordination is enabled: the requesting user is either channel, PNC or system user. 
        First check for channel users requesting full communication. PNC and system users are handled later. */   
        for(userIndex=0; userIndex < ComM_MaxNumberOfUsers; userIndex++)
        {
          if(ComM_PncUser[userIndex] == FALSE)
          {
            for(iByteMaskIndex = ComM_UserByteMaskIndex[userIndex]; iByteMaskIndex < ComM_UserByteMaskIndex[userIndex+1]; iByteMaskIndex++)
            {
#  if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
              if((ComM_IdentityMapping[ComM_UserByteMask[iByteMaskIndex].Channel] & ComM_ActiveIdentityMask) != 0u)
              {
#  endif
                /* PRQA S 0715 SUPPRESS_0715 */ /* MD_ComM_0715 */
                if(ComM_UserByteMask[iByteMaskIndex].Channel == Channel)
                {
                  if( (ComM_UserReqFullComArray[ComM_UserByteMask[iByteMaskIndex].ByteIndex] & ComM_UserByteMask[iByteMaskIndex].SetMask) > 0x00)
                  {
                    /* Found a channel user requesting FULL_COMM. The highest request mode shall be COMM_NETWORK_REQUESTED, unless there is an active mode limitation on the channel (checked later). */
                    lHighestRequest = COMM_NETWORK_REQUESTED;
                  }
                }
                /* PRQA L:SUPPRESS_0715 */
#  if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
              }
#  endif
            }
          }
        }
# else
        /* Case 1.2 - PNC coordination is disabled: the requesting user is either channel or PNC user.
        The highest request mode shall be COMM_NETWORK_REQUESTED, unless there is an active mode limitation on the channel (checked later). */
        lHighestRequest = COMM_NETWORK_REQUESTED;
# endif
      }
      else
      {
        /* Case 2 - PNC is disabled per postbuild or no PNC is assigned to the channel: the requesting user is a channel user.
        The highest request mode shall be COMM_NETWORK_REQUESTED, unless there is an active mode limitation on the channel (checked later). */
        lHighestRequest = COMM_NETWORK_REQUESTED;
      }
#else
      /* Case 3 - PNC support is disabled: the requesting user is always a channel user.
      The highest request mode shall be COMM_NETWORK_REQUESTED, unless there is an active mode limitation on the channel (checked later). */
      lHighestRequest = COMM_NETWORK_REQUESTED;
#endif

      /* check mode limitation state */
      if( ComM_NoComLimitationActive(Channel) == TRUE )
      {
        /* inhibition to NO COM is active */
        lHighestRequest = COMM_NO_COM;
      }

      /* check prevent wake up state */
      if( ComM_PreventWakeUpActive(Channel) == TRUE )
      {
        /* prevent wake up is activated */
        /* communication is not active, prevent wake up will be active */
        lHighestRequest = COMM_NO_COM;
      }
    }
  }/* for(lStopIndex = ComM_ChannelStopIndex[channel];(lStartIndex <= lStopIndex);lStartIndex++) */
  
  if( ComM_DcmRequestActive == TRUE )
  {
    /* the highest requested ComM mode if FULL COMMUNCIATION (Network requested if the DCM request is active 
     * or the current calcualed highest requested state is > silent mode */
    lHighestRequest = COMM_NETWORK_REQUESTED;
  }
  /* PRQA S 3689 1 */ /* MD_ComM_3689 */
  if(ComM_FrShutdown[Channel] == COMM_FR_SHUTDOWN_ACTIVE)
  {
    lHighestRequest = COMM_NO_COM;
  }

#if (COMM_PNC_SUPPORT == STD_ON)
  if( lHighestRequest == COMM_NETWORK_REQUESTED )
  {
    /* ESCAN00065332
     * There is no downgrade of highest request. If COMM_NETWORK_REQUESTED already detected, not needed to check PNCs */
  }
  else
  {
    if( (ComM_PncEnabled == TRUE) && (ComM_ChannelHasPnc[Channel] == TRUE) ) /* Consider only channels with at least one PNC assigned (ESCAN00073286) */
    {
      for(ComM_PnIdx=0; ComM_PnIdx < COMM_ACTIVE_PNC; ComM_PnIdx++)
      {
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
        for(ComM_PncChIdx = ComM_PnChannelStartIndex[ComM_PnIdx]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_PnIdx+1]; ComM_PncChIdx++)
        {
          if(ComM_PncChannelMapping[ComM_PncChIdx] == Channel)
          {
            /* Found a PN assigned to the current channel. Calculate the highest PN requested mode of all PNs on the channel */
            tmpPNComModeReq = ComM_CalculateHighestPNComMode(ComM_PnIdx, Channel);
            if( tmpPNComModeReq > highestPNComModeReq )
            {
              highestPNComModeReq = tmpPNComModeReq;
            }
# else
          if(ComM_PncChMap[ComM_PnIdx] == Channel)
          {
# endif /* COMM_PNC_ACTIVE_COORD == STD_ON */
            if(ComM_ActivePncComMode[ComM_PnIdx] > COMM_PNC_PREPARE_SLEEP)
            {
              /* At least one PN on this channel is in PNC_FULL_COMMUNICATION state. The channel shall be at least in COMM_READY_TO_SLEEP. */
              if(lHighestRequest == COMM_NO_COM)
              {
                lHighestRequest = COMM_READY_TO_SLEEP;
              }
            }
          }
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
        }
# endif
      }
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
      if( highestPNComModeReq == COMM_PNC_REQUESTED_PASSIVE )
      {
        /* At least one PN on the channel is in the highest possible mode (requested by a local PN user or via ERAm=1).
        The channel shall be requested actively. */
        lHighestRequest = COMM_NETWORK_REQUESTED;
      }
      else if( highestPNComModeReq == COMM_PNC_REQUESTED )
      {
        /* None of the PNs on the channel is in the highest possible mode, but at least one is requested via ERAp=1.
        The channel request depends on the GW type. */
        if( ComM_PncGwType[Channel] == COMM_GATEWAY_TYPE_ACTIVE )
        {
          /* Channels with GW type ACTIVE shall be requested actively. */
          lHighestRequest = COMM_NETWORK_REQUESTED;
        }
        else if( ComM_PncGwType[Channel] == COMM_GATEWAY_TYPE_PASSIVE )
        {
          /* Channels with GW type PASSIVE shall not be requested actively. */
          lHighestRequest = COMM_READY_TO_SLEEP;
        }
        else
        {
          /* Nothing to do */
        }
      }
      else
      {
        /* Nothing to do */
      }
# endif
    }
  }
#endif

  SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);

  return lHighestRequest;
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */

#if (COMM_PNC_SUPPORT == STD_ON)
/**********************************************************************************************************************
 FUNCTION:ComM_CalculateHighestPNComMode
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: uint8                   PN                      PN handle
          NetworkHandleType       Channel                 Channel Handle
  Output: -                       -                       -
  Return: ComM_SubModeType        -                       the current highest communciation mode

-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: ComM function ComM_MainFunction
  Precondition: -

  This fucntion calculates the current highest communication mode request for the PN
**********************************************************************************************************************/
STATIC FUNC( ComM_PncModeType, COMM_CODE) ComM_CalculateHighestPNComMode( uint8 PN, NetworkHandleType  Channel )
{
  ComM_PncModeType lHighestRequest;
  uint8         lStartIndex;
  uint8         lStopIndex;
  boolean       bModeLimit = FALSE;
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
  uint8         uTmpByte;
  uint8         uSysUserByteIndex;
  boolean       bPassivePnc = FALSE;
  boolean       bPnEraActive = FALSE;
  NetworkHandleType ComM_PncChIdx;
  
  ComM_DummyStatement( Channel ) /* PRQA S 3112 */ /* MD_ComM_3112 */
#endif

  lHighestRequest = COMM_PNC_NO_COMMUNICATION; /* default value is no communication */
  lStartIndex = 0x00;

  SchM_Enter_ComM(COMM_EXCLUSIVE_AREA_0);

  if(PN > 0x00) 
  {
    /* get the start index of the ComM user bit field */
    lStartIndex = (uint8)((uint8)(ComM_PncStopIndex[(PN - 0x01)]) + (uint8)0x01);
  }

  /* Iterate through PNC user request bytes in ComM_UserReqPncFullCom[] for the given PN. 
  lStartIndex and lStopIndex define the first and last byte respectively. */
  /* PRQA S 2462 1 */ /* MD_ComM_2462 */
  for(lStopIndex = ComM_PncStopIndex[PN]; lStartIndex <= lStopIndex; lStartIndex++)
  {
#if (COMM_PNC_ACTIVE_COORD == STD_ON)
    if( ComM_PncSynchronized[PN] == TRUE )
    {
      /* PN is synchronized, i.e. there is exactly one system user assigned to it and one uSysUserByteIndex. */
      uSysUserByteIndex = ComM_UserPncByteMaskIndex[ComM_PncSysUserHandle[PN]];
      if(lStartIndex == ComM_UserPncByteMask[uSysUserByteIndex].ByteIndex)
      {
        /* The byte ComM_UserReqPncFullCom[lStartIndex] contains request bit of the system user amongst others. */
        uTmpByte = ComM_UserReqPncFullCom[lStartIndex];
        uTmpByte &= ComM_UserPncByteMask[uSysUserByteIndex].ClearMask;
        if( uTmpByte > 0x00 )
        {
          /* Some ComM users (not the system user) have requested the PNC */
          lHighestRequest = COMM_PNC_REQUESTED_PASSIVE;
        }
        else if( (ComM_UserReqPncFullCom[lStartIndex] > 0x00) && (lHighestRequest < COMM_PNC_REQUESTED_PASSIVE) )
        {
          /* Only the system user request is set in the current request byte. The 2nd condition is to ensure that no other PNC user requests
          and lHighestRequest is not set to COMM_PNC_REQUESTED_PASSIVE already, i.e. to avoid that lHighestRequest decreases 
          from COMM_PNC_REQUESTED_PASSIVE to COMM_PNC_REQUESTED when iterating. */
          lHighestRequest = COMM_PNC_REQUESTED;
        }
        else
        {
          /* Nothing to do */
        }
      }
      else
      {
        /* The byte in ComM_UserReqPncFullCom[lStartIndex] contains request bits of PN users, but not the system user. */
        if(ComM_UserReqPncFullCom[lStartIndex] > 0x00)
        {
          /* Some ComM users (not the system user) have requested the PNC */
          lHighestRequest = COMM_PNC_REQUESTED_PASSIVE;
        }
      }
    }
    else
    {
      /* PN is not synchronized, i.e. there are no system user assigned to it. */
      if(ComM_UserReqPncFullCom[lStartIndex] > 0x00)
      {
        lHighestRequest = COMM_PNC_REQUESTED_PASSIVE;
      }
    }
#else
    {
      if(ComM_UserReqPncFullCom[lStartIndex] > 0x00) /* full request is set */
      {
        lHighestRequest = COMM_PNC_REQUESTED; /* set lHighestRequest to full communication*/ 
      }
    }
#endif

  }/* for */

#if (COMM_PNC_ACTIVE_COORD == STD_ON)

  for(ComM_PncChIdx = ComM_PnChannelStartIndex[PN]; ComM_PncChIdx < ComM_PnChannelStartIndex[PN+1]; ComM_PncChIdx++)
  {
    if( ComM_PncSynchronized[PN] == TRUE )
    {
      if(ComM_PncGwType[ComM_PncChannelMapping[ComM_PncChIdx]] == COMM_GATEWAY_TYPE_PASSIVE)
      {
        bPassivePnc = TRUE;
      }
      else if(ComM_PncGwType[ComM_PncChannelMapping[ComM_PncChIdx]] == COMM_GATEWAY_TYPE_ACTIVE)
      {
        if((EraValues[ComM_PncChannelMapping[ComM_PncChIdx]][ComM_PncInfoMask[PN].ByteIndex] & (ComM_PncInfoMask[PN].SetMask)) > 0u)
        {
          bPnEraActive = TRUE;
        }
      }
      else
      {
        /* Nothing to do. Both gateway types have been handled. */
      }
    }

    if( ComM_NoComLimitationActive(ComM_PncChannelMapping[ComM_PncChIdx]) == TRUE )
    {
      bModeLimit = TRUE;
    }

    if( ComM_PreventWakeUpActive(ComM_PncChannelMapping[ComM_PncChIdx]) == TRUE )
    {
      bModeLimit = TRUE;
    }
  }

  if( (bPassivePnc == TRUE) && (bPnEraActive == TRUE) )
  {
    lHighestRequest = COMM_PNC_REQUESTED_PASSIVE;
  }

#else
  if(ComM_PncChMap[PN] == Channel)
  {
    if( ComM_NoComLimitationActive(Channel) == TRUE )
    {
      bModeLimit = TRUE;
    }

    if( ComM_PreventWakeUpActive(Channel) == TRUE )
    {
      bModeLimit = TRUE;
    }
  }
#endif

  if(bModeLimit == TRUE)
  {
    lHighestRequest = COMM_PNC_NO_COMMUNICATION;
  }

  if(ComM_BusPncComModeReq[PN] > lHighestRequest)
  {
    lHighestRequest = ComM_BusPncComModeReq[PN];
  }
  else if( (ComM_PncPSleepTimer[PN] > 0) && (lHighestRequest <= COMM_PNC_PREPARE_SLEEP) )
  {
    lHighestRequest = COMM_PNC_PREPARE_SLEEP;
  }
  else
  {
    /* Nothing to do. Statement is needed for MISRA-C:2004 compliance (Rule 14.10). */
  }

  SchM_Exit_ComM(COMM_EXCLUSIVE_AREA_0);

  return lHighestRequest;
} /* PRQA S 6010, 6030, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */
#endif

/**********************************************************************************************************************
 FUNCTION:ComM_PreventWakeUpActive
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                      channel handle
  Output: -                       -                       -
  Return: boolean                 -                       -

-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: ComM function ComM_MainFunction
  Precondition: -

  This fucntion calculates the current highest communication mode request
**********************************************************************************************************************/
STATIC FUNC( boolean, COMM_CODE) ComM_PreventWakeUpActive( NetworkHandleType  Channel )
{
#if (COMM_MODE_LIMITATION == STD_ON) /* ESCAN00054786 */
  boolean retValue;

  retValue = FALSE;
  
  /* check if ECU can be use prevent wake up */
  if( (ComM_Inhibition.ComM_ECUGroupClassification & (uint8)0x01) == (uint8)0x01)
  {
    /* check if prevent wake up is active */
    if( (ComM_Inhibition.ComM_InhibitionStatus[Channel] & (uint8)0x01) == (uint8)0x01 )
    {
      if(ComM_ActiveComMode[Channel] == COMM_NO_COM )
      {
        retValue = TRUE;
      }
    }
  }

  return retValue;
#else
  ComM_DummyStatement( Channel ) /* PRQA S 3112 */ /* MD_ComM_3112 */
  return FALSE;
#endif
}


/**********************************************************************************************************************
 FUNCTION:ComM_NoComLimitationActive
-----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
-----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                      channel handle
  Output: -                       -                       -
  Return: boolean                 -                       -

-----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
     Called by: ComM function ComM_MainFunction
  Precondition: -

  This fucntion calculates the current highest communication mode request
**********************************************************************************************************************/
FUNC(boolean, COMM_CODE) ComM_NoComLimitationActive( NetworkHandleType  Channel )
{
  boolean retValue;

  retValue = FALSE;
  
  /* check if ECU can be limited to no com */
  if( (ComM_Inhibition.ComM_ECUGroupClassification & (uint8)0x02) == (uint8)0x02)
  {
    /* check if mode limitation to NO COM is active */
    if( (ComM_Inhibition.ComM_InhibitionStatus[Channel] & (uint8)0x02) == (uint8)0x02 )
    {
      retValue = TRUE;
    }
  }

  return retValue;
}


/**********************************************************************************************************************
  CALLBACK FUNCTIONS (AUTOSAR NM)
**********************************************************************************************************************/

/*********************************************************************************************************************
  FUNCTION: ComM_Nm_NetworkStartIndication
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                 channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR NM
  Precondition: ComM and NM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_Nm_NetworkStartIndication(CONST(NetworkHandleType, AUTOMATIC) Channel)
{
  uint8 ComM_Channel;
#if (COMM_PNC_SUPPORT == STD_ON)
  uint8 ComM_PnIdx;
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
  uint8 ComM_PncChIdx;
# endif
#endif

  if(ComM_SyncWakeUp == TRUE)
  {
    /* GW synchronous wake up is enabled, notify passive wake up to all ComM Channels */
    for(ComM_Channel=0; ComM_Channel < ComM_Active_Channel; ComM_Channel++)
    {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[ComM_Channel] & ComM_ActiveIdentityMask) != 0u)
      {
#endif
        if(ComM_ActiveComMode[ComM_Channel] < COMM_READY_TO_SLEEP)
        {
          if( (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_LIGHT) || (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_NONE) || (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_OSEK))
          {
            ComM_BusComModeReq[ComM_Channel] = COMM_NETWORK_REQUESTED;
          }
          else
          {
            ComM_BusComModeReq[ComM_Channel] = COMM_READY_TO_SLEEP;
#if (COMM_PNC_SUPPORT == STD_ON)
            if( (ComM_PncEnabled == TRUE) && (ComM_ChannelHasPnc[ComM_Channel] == TRUE) ) /* Consider only channels with at least one PNC assigned (ESCAN00073286) */
            {
              /* PRQA S 0715 SUPPRESS_0715 */ /* MD_ComM_0715 */
              if( ComM_PncPSTimer > 0 ) /* Activate PNCs only if ComMPncPrepareSleepTimer is configured > 0 (ESCAN00060976) */
              {
                for(ComM_PnIdx=0; ComM_PnIdx < ComM_PncCount; ComM_PnIdx++)
                {
#  if (COMM_PNC_ACTIVE_COORD == STD_ON)
                  for(ComM_PncChIdx=ComM_PnChannelStartIndex[ComM_PnIdx]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_PnIdx+1]; ComM_PncChIdx++)
                  {
                    if(ComM_PncChannelMapping[ComM_PncChIdx] == ComM_Channel)
#  else
                    if(ComM_PncChMap[ComM_PnIdx] == ComM_Channel)
#  endif
                    {
                      ComM_BusPncComModeReq[ComM_PnIdx] = COMM_PNC_PREPARE_SLEEP;
                    }
#  if (COMM_PNC_ACTIVE_COORD == STD_ON)
                  }
#  endif
                }
              }
              /* PRQA L:SUPPRESS_0715 */
            }
#endif
          }
        }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
#endif
    }
  }
  else
  {
    /* notify passive wake up of the Channel */
    if(ComM_Nm_Type[Channel] == NM_VARIANT_OSEK)
    {
      ComM_BusComModeReq[Channel] = COMM_NETWORK_REQUESTED;
    }
    else
    {
      ComM_BusComModeReq[Channel] = COMM_READY_TO_SLEEP;  /* set communication bus request to ready sleep*/
    }
  }

#if ( COMM_PROD_ERROR_DETECT == STD_ON )
  /* reception of Nm message in NO communication mode, report DEM failure */
  ComM_DemReportError(Channel);
#endif
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/*********************************************************************************************************************
  FUNCTION: ComM_Nm_NetworkMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                 channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR NM
  Precondition: ComM and NM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_Nm_NetworkMode(CONST(NetworkHandleType, AUTOMATIC) Channel)
{
  /* ESCAN00061901, ESCAN00069051:
  ComM immediately triggers CanSm to enter Full Com when ComM_Nm_NetworkMode is notified and ComM is in "Silent Mode"
  and Nm has notified ComM_Nm_PrepareBusSleepMode before it ( ComM_BusComModeReq[Channel] == COMM_SI_COM ).
  This ensures that NM message can be sent as first message on the bus. */
  
  if(ComM_Nm_Type[Channel] == NM_VARIANT_OSEK)
  {
    if(( ComM_ActiveComMode[Channel] == COMM_SI_COM ) && ( ComM_BusComModeReq[Channel] == COMM_SI_COM ))
    {
      ComM_ActiveComMode[Channel] = COMM_NETWORK_REQUESTED; /* Set the active mode first to ensure that condition is not re-entered */
      ComM_SICOM_NETREQ(Channel);
    }

    ComM_BusComModeReq[Channel] = COMM_NETWORK_REQUESTED;
  }
  else
  {
    if(( ComM_ActiveComMode[Channel] == COMM_SI_COM ) && ( ComM_BusComModeReq[Channel] == COMM_SI_COM ))
    {
      ComM_ActiveComMode[Channel] = COMM_READY_TO_SLEEP; /* Set the active mode first to ensure that condition is not re-entered */
      ComM_SICOM_READYS( Channel );
    }

    ComM_BusComModeReq[Channel] = COMM_READY_TO_SLEEP;
  }
}


/*********************************************************************************************************************
  FUNCTION: ComM_Nm_PrepareBusSleepMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                 channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR NM
  Precondition: ComM and NM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_Nm_PrepareBusSleepMode(CONST(NetworkHandleType, AUTOMATIC) Channel)
{
  ComM_BusComModeReq[Channel] = COMM_SI_COM;
  ComM_SICOM(Channel);

  ComM_ActiveComMode[Channel] = COMM_SI_COM;
}


/*********************************************************************************************************************
  FUNCTION: ComM_Nm_BusSleepMode
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                 channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR NM
  Precondition: ComM and NM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_Nm_BusSleepMode(CONST(NetworkHandleType, AUTOMATIC) Channel)
{
  if(ComM_ChannelBusType[Channel] == COMM_BUS_TYPE_FR)
  {
    ComM_FrShutdown[Channel] = COMM_FR_SHUTDOWN_ACTIVE;
  }

  ComM_BusComModeReq[Channel] = NO_COM;

  ComM_SICOM_NOCOM(Channel);

  if(ComM_ChannelBusType[Channel] == COMM_BUS_TYPE_FR)
  {
    if( (ComM_BusSmState[Channel] == COMM_NO_COMMUNICATION) && (ComM_FrShutdown[Channel] == COMM_FR_SHUTDOWN_ACTIVE))
    {
      ComM_FrShutdown[Channel] = COMM_FR_SHUTDOWN_DEACTIVE;
    }
  }

  ComM_ActiveComMode[Channel] = NO_COM;
}


/*********************************************************************************************************************
  FUNCTION: ComM_Nm_RestartIndication
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType  Channel                 channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: Autosar NM
  Precondition: ComM is correct initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_Nm_RestartIndication(CONST(NetworkHandleType, AUTOMATIC) Channel)
{
  uint8 ComM_Channel;
#if (COMM_PNC_SUPPORT == STD_ON)
  uint8 ComM_PnIdx;
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
  uint8 ComM_PncChIdx;
# endif
#endif

  if(ComM_SyncWakeUp == TRUE)
  {
    /* GW synchronous wake up is enabled, notify passive wake up to all ComM Channels */
    for(ComM_Channel=0; ComM_Channel < ComM_Active_Channel; ComM_Channel++)
    {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[ComM_Channel] & ComM_ActiveIdentityMask) != 0u)
      {
#endif
        /* notify passive wake up of the Channel */
        if(ComM_FrShutdown[ComM_Channel] == COMM_FR_SHUTDOWN_ACTIVE)
        {
          ComM_BusComModeReqTmp[ComM_Channel] = COMM_READY_TO_SLEEP;  /* FlexRay Shutdown in progress store bus request */
        }
        else
        {
          if(ComM_ActiveComMode[ComM_Channel] < COMM_READY_TO_SLEEP)
          {
            if( (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_LIGHT) || (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_NONE) || (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_OSEK))
            {
              ComM_BusComModeReq[ComM_Channel] = COMM_NETWORK_REQUESTED;
            }
            else
            {
              ComM_BusComModeReq[ComM_Channel] = COMM_READY_TO_SLEEP;
#if (COMM_PNC_SUPPORT == STD_ON)
              if( (ComM_PncEnabled == TRUE) && (ComM_ChannelHasPnc[ComM_Channel] == TRUE) ) /* Consider only channels with at least one PNC assigned (ESCAN00073286) */
              {
                /* PRQA S 0715 SUPPRESS_0715 */ /* MD_ComM_0715 */
                if( ComM_PncPSTimer > 0 ) /* Activate PNCs only if ComMPncPrepareSleepTimer is configured > 0 (ESCAN00060976) */
                {
                  for(ComM_PnIdx=0; ComM_PnIdx < ComM_PncCount; ComM_PnIdx++)
                  {
#  if (COMM_PNC_ACTIVE_COORD == STD_ON)
                    for(ComM_PncChIdx=ComM_PnChannelStartIndex[ComM_PnIdx]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_PnIdx+1]; ComM_PncChIdx++)
                    {
                      if(ComM_PncChannelMapping[ComM_PncChIdx] == ComM_Channel)
#  else
                      if(ComM_PncChMap[ComM_PnIdx] == ComM_Channel)
#  endif
                      {
                        ComM_BusPncComModeReq[ComM_PnIdx] = COMM_PNC_PREPARE_SLEEP;
                      }
#  if (COMM_PNC_ACTIVE_COORD == STD_ON)
                    }
#  endif
                  }
                }
                /* PRQA L:SUPPRESS_0715 */
              }
#  endif
            }
          }
        }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
#endif
    } /* For End */
  }
  else
  {
    /* notify passive wake up of the Channel */
    if(ComM_FrShutdown[Channel] == COMM_FR_SHUTDOWN_ACTIVE)
    {
      ComM_BusComModeReqTmp[Channel] = COMM_READY_TO_SLEEP;  /* set communication bus request to ready sleep*/
    }
    else
    {
      if(ComM_Nm_Type[Channel] == NM_VARIANT_OSEK)
      {
        ComM_BusComModeReq[Channel] = COMM_NETWORK_REQUESTED;
      }
      else
      {
        ComM_BusComModeReq[Channel] = COMM_READY_TO_SLEEP;  /* set communication bus request to ready sleep*/
      }
    }
  }
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/**********************************************************************************************************************
  CALLBACK FUNCTIONS (AUTOSAR DCM)
**********************************************************************************************************************/

/*********************************************************************************************************************
  FUNCTION: ComM_DCM_ActiveDiagnostic
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR Diagnostic Communication Manager
  Precondition: ComM and DCM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_DCM_ActiveDiagnostic(void)
{
  /* notify an active DCM diagnostic session */
  ComM_DcmRequestActive = TRUE;
}


/*********************************************************************************************************************
  FUNCTION: ComM_DCM_InactiveDiagnostic
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR Diagnostic Communication Manager
  Precondition: ComM and DCM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_DCM_InactiveDiagnostic(void)
{
  /* notify the end of a DCM diagnostic session */
  ComM_DcmRequestActive = FALSE;
}


/**********************************************************************************************************************
  CALLBACK FUNCTIONS (AUTOSAR EcuM)
**********************************************************************************************************************/

/*********************************************************************************************************************
  FUNCTION: ComM_EcuM_RunModeIndication
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: -
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR Ecu State Manager
  Precondition: ComM and EcuM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_EcuM_RunModeIndication(const NetworkHandleType Channel)
{
  ComM_DummyStatement( Channel ) /* PRQA S 3112 */ /* MD_ComM_3112 */

  /* nothing to do */
}


/*********************************************************************************************************************
  FUNCTION: ComM_EcuM_WakeUpIndication
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: ComM_ChannelHandleType  Channel                 channel handle
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR Ecu State Manager
  Precondition: ComM and EcuM are initialized

  
*********************************************************************************************************************/
FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication(const NetworkHandleType Channel)
{
  uint8 ComM_Channel;
#if (COMM_PNC_SUPPORT == STD_ON)
  uint8 ComM_PnIdx;
# if (COMM_PNC_ACTIVE_COORD == STD_ON)
  uint8 ComM_PncChIdx;
# endif
#endif

  if(ComM_SyncWakeUp == TRUE)
  {
    /* GW synchronous wake up is enabled, notify passive wake up to all ComM Channels */
    for(ComM_Channel=0; ComM_Channel < ComM_Active_Channel; ComM_Channel++)
    {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      if((ComM_IdentityMapping[ComM_Channel] & ComM_ActiveIdentityMask) != 0u)
      {
#endif
        if(ComM_ActiveComMode[ComM_Channel] < COMM_READY_TO_SLEEP)
        {
          if( (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_LIGHT) || (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_NONE) || (ComM_Nm_Type[ComM_Channel] == NM_VARIANT_OSEK))
          {
            ComM_BusComModeReq[ComM_Channel] = COMM_NETWORK_REQUESTED;
          }
          else
          {
            ComM_BusComModeReq[ComM_Channel] = COMM_READY_TO_SLEEP;
#if (COMM_PNC_SUPPORT == STD_ON)
            if( (ComM_PncEnabled == TRUE) && (ComM_ChannelHasPnc[ComM_Channel] == TRUE) ) /* Consider only channels with at least one PNC assigned (ESCAN00073286) */
            {
              /* PRQA S 0715 SUPPRESS_0715 */ /* MD_ComM_0715 */
              if( ComM_PncPSTimer > 0 ) /* Activate PNCs only if ComMPncPrepareSleepTimer is configured > 0 (ESCAN00060976) */
              {
                for(ComM_PnIdx=0; ComM_PnIdx < ComM_PncCount; ComM_PnIdx++)
                {
#  if (COMM_PNC_ACTIVE_COORD == STD_ON)
                  for(ComM_PncChIdx=ComM_PnChannelStartIndex[ComM_PnIdx]; ComM_PncChIdx < ComM_PnChannelStartIndex[ComM_PnIdx+1]; ComM_PncChIdx++)
                  {
                    if(ComM_PncChannelMapping[ComM_PncChIdx] == ComM_Channel)
#  else
                    if(ComM_PncChMap[ComM_PnIdx] == ComM_Channel)
#  endif
                    {
                      ComM_BusPncComModeReq[ComM_PnIdx] = COMM_PNC_PREPARE_SLEEP;
                    }
#  if (COMM_PNC_ACTIVE_COORD == STD_ON)
                  }
#  endif
                }
              }
              /* PRQA L:SUPPRESS_0715 */
            }
#endif
          }
        }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
      }
#endif
    }
  }
  else
  {
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
    if((ComM_IdentityMapping[Channel] & ComM_ActiveIdentityMask) != 0u)
    {
#endif
      if( (ComM_Nm_Type[Channel] == NM_VARIANT_LIGHT) || (ComM_Nm_Type[Channel] == NM_VARIANT_NONE) || (ComM_Nm_Type[Channel] == NM_VARIANT_OSEK))
      {
        ComM_BusComModeReq[Channel] = COMM_NETWORK_REQUESTED;
      }
      else
      {
        /* notify passive wake up of the Channel */
        ComM_BusComModeReq[Channel] = COMM_READY_TO_SLEEP;  /* set communication bus request to ready sleep*/
      }
#if (COMM_IDENTITY_MANAGER_CONFIG == STD_ON)
    }
#endif
  }
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */


/**********************************************************************************************************************
  CALLBACK FUNCTIONS (AUTOSAR BusSm)
**********************************************************************************************************************/

/*********************************************************************************************************************
  FUNCTION: ComM_BusSM_ModeIndication
----------------------------------------------------------------------------------------------------------------------
  API     Type                    Name                    Description
----------------------------------------------------------------------------------------------------------------------
   Input: NetworkHandleType       Channel                 channel handle
          ComM_ModeType           ComM_Mode               communication mode
  Output: -
  Return: -
----------------------------------------------------------------------------------------------------------------------
  FUNCTION DESCRIPTION
----------------------------------------------------------------------------------------------------------------------
     Called by: AUTOSAR LIN, CAN or Flexray state manager 
  Precondition: ComM is initialized

  The function is called if a bus state manager indicates a new commmunication mode.
*********************************************************************************************************************/
/* PRQA S 3673 1 */ /* MD_ComM_3673 */
FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication(NetworkHandleType Channel, P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_VAR) ComM_Mode)
{
  if(*ComM_Mode == COMM_FULL_COMMUNICATION)
  {
    ComM_BusSmState[Channel] = COMM_FULL_COMMUNICATION;

    if(ComM_LastBusSmState[Channel] != COMM_FULL_COMMUNICATION)
    {
      /* BusSM mode for this channel has changed to COMM_FULL_COMMUNICATION */
      ComM_DcmIndication(); /* ESCAN00062631 */
      ComM_LastBusSmState[Channel] = COMM_FULL_COMMUNICATION;
      ComM_StateChange[Channel] = COMM_FULL_COMMUNICATION;
    }
  }

  if((*ComM_Mode == COMM_SILENT_COMMUNICATION))
  {
    ComM_BusSmState[Channel] = COMM_SILENT_COMMUNICATION;

    if(ComM_LastBusSmState[Channel] != COMM_SILENT_COMMUNICATION)
    {
      /* BusSM mode for this channel has changed to COMM_SILENT_COMMUNICATION */
      ComM_DcmIndication(); /* ESCAN00062631 */
      ComM_LastBusSmState[Channel] = COMM_SILENT_COMMUNICATION;
      ComM_StateChange[Channel] = COMM_SILENT_COMMUNICATION;
    }
  }

  if(*ComM_Mode == COMM_NO_COMMUNICATION)
  {
    ComM_BusSmState[Channel] = COMM_NO_COMMUNICATION;
    if(ComM_ChannelBusType[Channel] == COMM_BUS_TYPE_FR)
    {
      ComM_FrShutdown[Channel] = COMM_FR_SHUTDOWN_DEACTIVE;

      if(ComM_BusComModeReqTmp[Channel] == COMM_READY_TO_SLEEP)
      {
        ComM_BusComModeReqTmp[Channel] = NO_COM;        /* set temp communication bus request to no communciation */
        ComM_BusComModeReq[Channel] = COMM_READY_TO_SLEEP;  /* set communication bus request to ready sleep*/
      }
    }

    if(ComM_LastBusSmState[Channel] != COMM_NO_COMMUNICATION)
    {
      /* BusSM mode for this channel has changed to COMM_NO_COMMUNICATION */      
      ComM_DcmIndication();/* ESCAN00062631 */
      ComM_LastBusSmState[Channel] = COMM_NO_COMMUNICATION;
      ComM_StateChange[Channel] = COMM_NO_COMMUNICATION;
    }

    ComM_EnterModeNoCommunication(Channel);
  }
}

/* module specific MISRA deviations:
MD_ComM_3218:
      Reason:     Table is defined outside the function because of known problems with some compilers whihc can not handle STATIC CONST inside functions.
      Risk:       There is no risk..
      Prevention: N/A
MD_ComM_3415:
      Reason:     Functions only return the TRUE or FALSE status of the checked ComM channel.
      Risk:       There is no risk..
      Prevention: Covered by code review.
MD_ComM_2462:
      Reason:     The variables are always set to a defined value before it is used.
      Risk:       There is no risk..
      Prevention: Covered by code review.
MD_ComM_3112:
      Reason:     Dummy statement to avoid compiler warnings.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Covered by code review.
MD_ComM_3673:
      Reason:     The function parameter list is required by the AUTOAR specification.
      Risk:       There is no risk.
      Prevention: N/A.
MD_ComM_3689:
      Reason:     The function ComM_CalculateHighestComMode is only called from the ComM_MainFunction, this function ensures that the Channel handle is in a vaild range.
      Risk:       There is no risk.
      Prevention: Covered by code review.
MD_ComM_3684:
      Reason:     Avoid libraries with arrays which contain only one single element caused by compiler optimization.
      Risk:       none
      Prevention: Covered by code review.
MD_ComM_3453:
      Reason:     Since efficiency is a primary implementation target it is necessary to use macros.
      Risk:       none
      Prevention: Covered by code review.
MD_ComM_0505:
      Reason:     Buffer pointer is provided by caller. API checks for validity and calls DET in case of NULL pointer.
      Risk:       NULL pointer dereferencing leads to unexpected behavior.
      Prevention: Pointer value is validated by previous assertion. It is recommended to stop further code execution if any assertion fails.
MD_ComM_1281:
      Reason:     Significant effort and risk of side-effects when generating constants with "u" suffix. 
      Risk:       There is no risk. Constants will be correctly assigned to uint32 struct members since the number base is hexadecimal and there are no calculations before assignment.
      Prevention: Covered by code review.
MD_ComM_3200:
      Reason:     Return value of ComM_RequestComMode() shall be checked if the function is called by the application. It shall not be checked if called within the ComM component.
                  Correctness of parameters passed to the function is ensured by code review.
      Risk:       There is no risk.
      Prevention: Covered by code review.
MD_ComM_0781:
      Reason:     Local variable and a struct element have the same identifier. This is because the one is the local copy of the other for a faster access because of multiple usages.
      Risk:       There is no risk.
      Prevention: Covered by code review.
MD_ComM_2018:
      Reason:     Default label is provided as a defensive measure against possible future code changes and to comply with rule 15.3.
      Risk:       There is no risk.
      Prevention: Covered by code review.
MD_ComM_0715:
      Reason:     Nested control structures required due to complex iteration and condition implementation.
      Risk:       Compiler warning / error.
      Prevention: Verified at integration with target compiler.
*/

#define COMM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"
/* STOPSINGLE_OF_MULTIPLE */
