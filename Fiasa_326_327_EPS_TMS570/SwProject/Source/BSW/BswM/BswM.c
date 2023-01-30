/* Kernbauer Version: 1.14 Konfiguration: BswM Erzeugungsgangnummer: 23 */


/* KB begin BswM_Header */
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2011-2014 by Vector Informatik GmbH.                                             All rights reserved.
 * 
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  BswM.c
 *      Project:  SysService_AsrBswM
 *       Module:  MICROSAR Basic Software Mode Manager
 *    Generator:  
 *
 *  Description:  Implements AUTOSAR BswM
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Patrick Markl                 visml         Vector Informatik GmbH
 *  Daniel Hof                    visdhf        Vector Informatik GmbH
 *  Thomas Kuhl                   vispet        Vector Informatik GmbH
 *  Leticia Garcia Herrera        visgle        Vector Informatik GmbH
 *  
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2011-01-17  visml   ESCAN00046216 Creation
 *                        visdhf
 *  01.01.00  2011-04-04  visdhf  ESCAN00049801: added NM Fiat support
 *  01.02.00  2011-06-16  visdhf  ESCAN00049881: added Partial Networks support
 *                                ESCAN00051663: removed AR version check
 *                                ESCAN00051684: extended Det error checks
 *                                ESCAN00051685: changed implementation of BswM_LinSM_CurrentSchedule() 
 *                                ESCAN00051934: changed call of BswM_Init_Gen
 *                                ESCAN00051949: added definition of BswM_Dcm_SetPassiveMode()
 *                                ESCAN00052907: added ASR SWS version defines
 *  01.02.01  2011-11-03  vispet  ESCAN00054123: Remove unnecessary variable extern declaration
 *  01.03.00  2011-11-25  vispet  ESCAN00053583: AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053609: AR3-2069: Remove non-SchM code for critical section handling
 *                                ESCAN00054142: Missing functionality of BswM_Dcm_ApplicationUpdated
 *  01.04.00  2012-03-19  vispet  ESCAN00056682: AR3-2357 Support Mode Switch notification for SWC
 *                                ESCAN00058090: Remove preprocessor defines V_CRITICAL_SECTION_USE_SCHM_COMMENT
 *                                ESCAN00058091: Add BswM Timer Handling
 *  01.05.00  2012-06-26  vispet  ESCAN00057762: Remove DCM_RESET_EXECUTION from the Dcm_ResetModeType
 *  01.06.00  2012-08-28  vispet  ESCAN00057856: Adapt LinTp_Modes to AUTOSAR specification
 *                                ESCAN00060095: AR3-2429: Add Support for LinSM schedule end notification
 *  01.06.01  2012-10-17  vispet  ESCAN00062295: Rules with Schedule Table end notification not evaluated
 *  01.07.00  2013-04-04  visgle  ESCAN00066117: AR3-2494: Implement AMD timemeasurement support
 *            2013-04-08  visgle  ESCAN00066271: no changes
 *            2013-05-15  visgle  ESCAN00062683: Compiler error: LINTP_DIAG_RESPONSE
 *  01.08.00  2013-09-25  visgle  ESCAN00065553: BswM_ApplUpdateRequest processing optimization in the BswM_MainFunction
 *                                ESCAN00065554: BswM_Dcm_RequestResetMode optimization
 *                                ESCAN00069773: AR3-2562: first message after restart or startup must be the Nm message
 *                                ESCAN00070914: no changes
 *                                ESCAN00071083: BswM_MainFunction() runtime optimization
 *  01.09.00  2014-30-01  visgle  ESCAN00068671: Improve runtime of BswM_MainFunction by changing timer handling
 *                                ESCAN00071426: Compiler Error: 'LINTP_APPLICATIVE_SCHEDULE' : undeclared identifier
 *********************************************************************************************************************/

/* KB end BswM_Header */

#define BSWM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "BswM.h"
#if ( BSWM_DEV_ERROR_DETECT == STD_ON )
# include "Det.h"
#endif

# include "SchM_BswM.h"


#if defined (V_SUPPRESS_EXTENDED_VERSION_CHECK)
#else
# include "v_ver.h"
#endif

#if ((defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )) || ( BSWM_CRC_CHECK == STD_ON ))
#else
# include "EcuM_Cbk.h"
#endif

#if ( BSWM_ENABLE_DCM_PASSIVE_MODE == STD_ON )
# if (BSWM_ENABLE_FR_PASSIVE_MODE == STD_ON)
#  include "FrSM.h"
# endif

# if (BSWM_ENABLE_CAN_PASSIVE_MODE == STD_ON)
#  include "CanSM.h"
# endif
#endif

#if (BSWM_AMD_RUNTIME_MEASUREMENT == STD_ON)
# include "AmdRtm.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if((BSWM_SW_MAJOR_VERSION != (0x01)) || \
    (BSWM_SW_MINOR_VERSION != (0x09)) || \
    (BSWM_SW_PATCH_VERSION != (0x00)) )
# error "Vendor specific version numbers of BswM.c and BswM.h are inconsistent"
#endif

#if (( BSWM_ENABLE_DCM_RESET == STD_ON ) || ( BSWM_ENABLE_DCM_COMTRL == STD_ON ))
# if((BSWM_DCM_MAJOR_VERSION != (0x01)) || \
    ( BSWM_DCM_MINOR_VERSION != (0x09)) || \
    ( BSWM_DCM_PATCH_VERSION != (0x00)) )
#  error "BswM_Dcm.h version is not correct!"
# endif
#endif

#if ( BSWM_ENABLE_FRSM == STD_ON )
# if((BSWM_FRSM_MAJOR_VERSION != (0x01)) || \
    ( BSWM_FRSM_MINOR_VERSION != (0x09)) || \
    ( BSWM_FRSM_PATCH_VERSION != (0x00)) )
#  error "BswM_FrSM.h version is not correct!"
# endif
#endif

#if ( BSWM_ENABLE_CANSM == STD_ON )
# if((BSWM_CANSM_MAJOR_VERSION != (0x01)) || \
    ( BSWM_CANSM_MINOR_VERSION != (0x09)) || \
    ( BSWM_CANSM_PATCH_VERSION != (0x00)) )
#  error "BswM_CanSM.h version is not correct!"
# endif
#endif

#if ( BSWM_ENABLE_LINSM == STD_ON )
# if((BSWM_LINSM_MAJOR_VERSION != (0x01)) || \
    ( BSWM_LINSM_MINOR_VERSION != (0x09)) || \
    ( BSWM_LINSM_PATCH_VERSION != (0x00)) )
#  error "BswM_LinSM.h version is not correct!"
# endif
#endif

#if ( BSWM_ENABLE_LINTP == STD_ON )
# if((BSWM_LINTP_MAJOR_VERSION != (0x01)) || \
    ( BSWM_LINTP_MINOR_VERSION != (0x09)) || \
    ( BSWM_LINTP_PATCH_VERSION != (0x00)) )
#  error "BswM_LinTp.h version is not correct!"
# endif
#endif

#if ( BSWM_ENABLE_NM == STD_ON )
# if((BSWM_NM_MAJOR_VERSION != (0x01)) || \
    ( BSWM_NM_MINOR_VERSION != (0x09)) || \
    ( BSWM_NM_PATCH_VERSION != (0x00)) )
#  error "BswM_Nm.h version is not correct!"
# endif
#endif

# if((BSWM_COMM_MAJOR_VERSION != (0x01)) || \
    ( BSWM_COMM_MINOR_VERSION != (0x09)) || \
    ( BSWM_COMM_PATCH_VERSION != (0x00)) )
#  error "BswM_ComM.h version is not correct!"
# endif


/*********************************************************************************************************************
 * Precompile checks                                                                                       
 *********************************************************************************************************************/
#if(BSWM_USER_COUNT == 0)
# error "BswM: configuration error, no rule configured, at least on rule must be configured!"
#endif



/*********************************************************************************************************************
 * Development Error Detection                                                                                       
 *********************************************************************************************************************/
#if(BSWM_DEV_ERROR_DETECT == STD_ON)
# define BswM_Det_ReportError(Condition, ApiId, ErrorCode)                    do                                                            \
                                                                              {                                                             \
                                                                                if(!(Condition))                                            \
                                                                                {                                                           \
                                                                                  Det_ReportError(BSWM_MODULE_ID, 0, (ApiId), (ErrorCode)); \
                                                                                }                                                           \
                                                                              }                                                             \
                                                                              while(0)
# define BswM_Det_ReportErrorReturnValue(Condition, ApiId, ErrorCode, RetVal) do                                                            \
                                                                              {                                                             \
                                                                                if(!(Condition))                                            \
                                                                                {                                                           \
                                                                                  Det_ReportError(BSWM_MODULE_ID, 0, (ApiId), (ErrorCode)); \
                                                                                  /* PRQA S 2006 */ /* MD_BswM_2006 */ return(RetVal);      \
                                                                                }                                                           \
                                                                              }                                                             \
                                                                              while(0)                                                                           
# define BswM_Det_ReportErrorReturn(Condition, ApiId, ErrorCode)              do                                                             \
                                                                              {                                                              \
                                                                                if(!(Condition))                                             \
                                                                                {                                                            \
                                                                                  Det_ReportError(BSWM_MODULE_ID, 0, (ApiId), (ErrorCode));  \
                                                                                  /* PRQA S 2006 */ /* MD_BswM_2006 */ return;               \
                                                                                }                                                            \
                                                                              }                                                              \
                                                                              while(0)
#else
# define BswM_Det_ReportError(Condition, ApiId, ErrorCode)
# define BswM_Det_ReportErrorReturnValue(Condition, ApiId, ErrorCode, RetVal)
# define BswM_Det_ReportErrorReturn(Condition, ApiId, ErrorCode)
#endif


#define BswM_EnterCriticalArea(a)      SchM_Enter_BswM(BSWM_EXCLUSIVE_AREA_0) /* PRQA S 3453 1 */ /* MD_BswM_3453 */
#define BswM_LeaveCriticalArea(a)      SchM_Exit_BswM(BSWM_EXCLUSIVE_AREA_0) /* PRQA S 3453 1 */ /* MD_BswM_3453 */


#define BSWM_REQUEST_SEMAPHORE_UNLOCKED   (0u)
#define BSWM_REQUEST_SEMAPHORE_LOCKED     (1u)

#if(BSWM_USER_COUNT > 255)
# define BSWM_USER_COMPARE_VALUE ((uint16)0xFFFF)
#else
# define BSWM_USER_COMPARE_VALUE ((uint8)0xFF)
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

#if(BSWM_DEV_ERROR_DETECT == STD_ON)
/* Initialization status of the BswM */
typedef enum 
{
  BSWM_UNINIT = 0,
  BSWM_INIT
}BswM_InitStatusType;
#endif

typedef struct
{
  uint8         modeRequestPending;
  BswM_ModeType requestedMode;
}BswM_ModeRequestQueueType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#define BSWM_START_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

STATIC VAR(uint8, BSWM_VAR_NOINIT) BswM_QueueSemaphore;

#define BSWM_STOP_SEC_VAR_NOINIT_8BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define BSWM_START_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

STATIC VAR(BswM_ModeRequestQueueType, BSWM_VAR_NOINIT) BswM_ModeRequestQueue[BSWM_USER_COUNT];

#if ( BSWM_ENABLE_DCM_APPL_UPDATE == STD_ON )
STATIC VAR(boolean, BSWM_VAR_NOINIT) BswM_ApplUpdateRequest;
#endif

#define BSWM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/
#define BSWM_START_SEC_VAR_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#if(BSWM_DEV_ERROR_DETECT == STD_ON)
STATIC VAR(BswM_InitStatusType, BSWM_VAR_INIT) BswM_InitStatus = BSWM_UNINIT;
#endif

#define BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/
#define BSWM_START_SEC_CONST_32BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

#if !defined (V_SUPPRESS_EXTENDED_VERSION_CHECK)
CONST(uint32, BSWM_CONST) SYSSERVICE_ASRBSWM_LIB_SYMBOL = SYSSERVICE_ASRBSWM_LIB_VERSION;
#endif

#define BSWM_STOP_SEC_CONST_32BIT
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define BSWM_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/
STATIC FUNC(void, BSWM_CODE) BswM_ProcessQueuedRequests(void);
STATIC FUNC(BswM_UserType, BSWM_CODE) BswM_GetUserHandle(BswM_UserDomainType domain, NetworkHandleType Network );


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************/
/*! \brief      Initializes the BSW Mode Manager module variables in case a initializing startup code is not used.
*   \param[in]  None
*   \param[out] None
*   \return     None
*   \pre        None
*   \context    Task context
*   \note       If this function is used it shall be called before any other BSWM function after startup.
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_InitMemory(void)
{
#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_InitStatus     = BSWM_UNINIT;
#endif
}


/***********************************************************************************************************************/
/*! \brief      Initializes the BSW Mode Manager.
*   \param[in]  ConfigPtr: Pointer to post-build configuration data
*   \param[out] None
*   \return     None
*   \pre        None
*   \context    Task context
*   \note       None
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Init(P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_PBCFG) ConfigPtr)
{
  BswM_UserType i;

#if(BSWM_IDENTITY_MANAGER_CONFIG == STD_OFF)
# if (V_USE_DUMMY_STATEMENT == STD_ON)
  (void)ConfigPtr; /* PRQA S 3112 */ /* MD_BswM_3112 */
# endif
#else
# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn(NULL_PTR != ConfigPtr, BSWM_INIT_ID, BSWM_E_NULL_POINTER);
# endif
#endif

#if ( BSWM_CRC_CHECK == STD_ON )
    if (BswM_PrecompileCRC != BSWM_PRECOMPILE_CRC)
    {
      EcuM_GeneratorCompatibilityError((uint16) BSWM_MODULE_ID, (uint8) 0u);
      /* PRQA S 2006 */ /* MD_BswM_2006 */
      return;
    }
#endif

#if !defined ( V_SUPPRESS_EXTENDED_VERSION_CHECK )
 if(((BswM_GeneratorVersion & 0x00FFFF00)!=
      (((uint32)SYSSERVICE_ASRBSWM_GENTOOL_GENY_MAJOR_VERSION<<16) | ((uint32)SYSSERVICE_ASRBSWM_GENTOOL_GENY_MINOR_VERSION<<8)))
# if defined (SYSSERVICE_ASRBSWM_GENTOOL_GENY_PATCH_VERSION )
#  if (SYSSERVICE_ASRBSWM_GENTOOL_GENY_PATCH_VERSION != 0)
      || ((BswM_GeneratorVersion & (uint32) 0x000000FF) < SYSSERVICE_ASRBSWM_GENTOOL_GENY_PATCH_VERSION)
#  endif
# endif
    )
  {
    EcuM_GeneratorCompatibilityError((uint16) BSWM_MODULE_ID, (uint8) 0);
    /* PRQA S 2006 */ /* MD_BswM_2006 */
    return; /* Do not continue with the initialization of the component the application may be influenced critically. */
  }
#endif

  BswM_QueueSemaphore = 0;

  for(i = 0; i < BSWM_USER_COUNT; i++)
  {
    BswM_ModeRequestQueue[i].modeRequestPending = 0;
    BswM_ModeRequestQueue[i].requestedMode = 0;
  }

#if ( BSWM_ENABLE_DCM_APPL_UPDATE == STD_ON )
  BswM_ApplUpdateRequest = FALSE;
#endif

  BswM_Init_Gen(ConfigPtr);

#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_InitStatus = BSWM_INIT;
#endif
}/* PRQA S 2006 */ /* MD_BswM_2006 */


/***********************************************************************************************************************/
/*! \brief      Deinitializes the BSW Mode Manager.
*   \param[in]  None
*   \param[out] None
*   \return     None
*   \pre        None
*   \context    Task context
*   \note       None
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Deinit(void)
{
  BswM_UserType i;

#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_InitStatus = BSWM_UNINIT;
#endif

  BswM_EnterCriticalArea(0);

  for(i = 0; i < BSWM_USER_COUNT; i++)
  {
    BswM_ModeRequestQueue[i].modeRequestPending = 0;
    BswM_ModeRequestQueue[i].requestedMode = 0;
  }
  
  BswM_LeaveCriticalArea(0);
}


/***********************************************************************************************************************/
/*! \brief      Called by immediate mode request functions in order to process other pending immediate requests
*   \param[in]  None
*   \param[out] None
*   \return     None
*   \pre        None
*   \context    Task context
*   \note       Global queue semaphore is still locked because this function is called from within a mode request call.
***********************************************************************************************************************/
STATIC FUNC(void, BSWM_CODE) BswM_ProcessQueuedRequests(void)
{
  BswM_UserType i;
  uint8 ruleIndex;
  BswM_RuleTableFctPtrType pRuleFct = NULL_PTR;
  
  for(i = 0; i < BSWM_USER_COUNT; i++)
  {
    while(1 == BswM_ModeRequestQueue[i].modeRequestPending)
    {
      BswM_ModeRequestQueue[i].modeRequestPending = 0;
     
      for( ruleIndex = 0; ruleIndex < BswM_UserConfig[i].NrOfRules; ruleIndex++ )
      {
        if( pRuleFct != BswM_UserConfig[i].RuleFctPtr[ruleIndex] )
        {
          pRuleFct = BswM_UserConfig[i].RuleFctPtr[ruleIndex];
          if(NULL_PTR != pRuleFct)
          { 
            (void)pRuleFct();
          }
        }
      }
    }
  }
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/***********************************************************************************************************************/
/*! \brief      Called by Bsw mode indications to get the BswM user handle
*   \param[in]  domain, Network
*   \param[out] None
*   \return     user handle
*   \pre        None
*   \context    Task context
*   \note       -
***********************************************************************************************************************/
STATIC FUNC(BswM_UserType, BSWM_CODE) BswM_GetUserHandle(BswM_UserDomainType domain, NetworkHandleType Network )
{
  BswM_UserType i;
  BswM_UserType userIndex = (BswM_UserType)0xFFu;

  for(i = 0; i < BSWM_USER_COUNT; i ++)
  {
    if( BswM_UserConfig[i].domain == domain )
    {
      if( BswM_UserConfig[i].network == Network )
      {
        userIndex = i;
        break;
      }
    }
  }

  return userIndex;
}


#if(BSWM_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************/
/*! \brief      Returns the version information of this module.
*   \param[in]  None
*   \param[out] VersionInfo: Pointer to where to store the version information of the module.
*   \return     None
*   \pre        None
*   \context    No restrictions
*   \note       The caller must ensure to allocate a variable of the type Std_VersionInfoType before the function call.
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, BSWM_APPL_DATA) VersionInfo)
{
#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn(NULL_PTR != VersionInfo, BSWM_GETVERSIONINFO_ID, BSWM_E_NULL_POINTER);
#endif

  VersionInfo -> vendorID         = (uint16) BSWM_VENDOR_ID;
  VersionInfo -> moduleID         = (uint8)  BSWM_MODULE_ID;
  VersionInfo -> instanceID       = (uint8)  0x00u;
  VersionInfo -> sw_major_version = (uint8)  BSWM_SW_MAJOR_VERSION;
  VersionInfo -> sw_minor_version = (uint8)  BSWM_SW_MINOR_VERSION;
  VersionInfo -> sw_patch_version = (uint8)  BSWM_SW_PATCH_VERSION;
}/* PRQA S 2006 */ /* MD_BswM_2006 */
#endif

/**********************************************************************************************************************/
/*! \brief      Generic function call to request modes. This function shall only be used by other BSW modules that 
*               do not have a specific mode request interface.
*   \param[in]  requesting_user: The user that requests the mode.
*   \param[in]  requested_mode:  The requested mode.
*   \param[out] None
*   \return     Std_ReturnType: 
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(Std_ReturnType, BSWM_CODE) BswM_RequestMode(BswM_UserType requesting_user, BswM_ModeType requested_mode)
{
  uint8 localSemaphore, i;
  BswM_RuleTableFctPtrType pRuleFct = NULL_PTR;

#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturnValue((BSWM_INIT == BswM_InitStatus), BSWM_REQUESTMODE_ID, BSWM_E_NO_INIT, E_NOT_OK);            
#endif

  BswM_EnterCriticalArea(0);
  localSemaphore = BswM_QueueSemaphore;
  if(BswM_QueueSemaphore == BSWM_REQUEST_SEMAPHORE_UNLOCKED)
  { 
    BswM_QueueSemaphore = BSWM_REQUEST_SEMAPHORE_LOCKED;
  } 
  BswM_LeaveCriticalArea(0);

  if(BSWM_RULE_IMMEDIATE == BswM_UserConfig[requesting_user].modeExecContext)
  {
    /* Check for interruption */
    if(BSWM_REQUEST_SEMAPHORE_LOCKED == localSemaphore)
    { 
      BswM_ModeRequestQueue[requesting_user].modeRequestPending = 1;
      BswM_ModeRequestQueue[requesting_user].requestedMode      = requested_mode;
    }
    else
    {
      for( i = 0; i < BswM_UserConfig[requesting_user].NrOfRules; i++ )
      {
        if( pRuleFct != BswM_UserConfig[requesting_user].RuleFctPtr[i] )
        {
          pRuleFct = BswM_UserConfig[requesting_user].RuleFctPtr[i];
          if(NULL_PTR != pRuleFct)
          { 
            (void)pRuleFct();
          }
        }
      }
    }
  }


  if(BSWM_REQUEST_SEMAPHORE_UNLOCKED == localSemaphore)
  {
    /* Immediately process other pending immediate requests */
    BswM_ProcessQueuedRequests();
    
    /* Unlock semaphore AFTER processing of the queue */
    BswM_QueueSemaphore = BSWM_REQUEST_SEMAPHORE_UNLOCKED;
  }
  

  return(E_OK);
} /* PRQA S 2006, 6080 */ /* MD_BswM_2006, MD_MSR_STMIF */



/**********************************************************************************************************************/
/*! \brief      Function called by ComM to indicate the current communication mode of a ComM channel.
*   \param[in]  Network      : The ComM communication channel that the indicated state corresponds to.
*   \param[in]  RequestedMode: The current state of the ComM communication channel
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_ComM_CurrentMode(NetworkHandleType Network, ComM_ModeType RequestedMode)
{
  BswM_UserType localUserHandle;
  
#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_COMM_CURRENTMODE_ID, BSWM_E_NO_INIT);
  BswM_Det_ReportErrorReturn(((RequestedMode == COMM_NO_COMMUNICATION) || (RequestedMode == COMM_FULL_COMMUNICATION) || (RequestedMode == COMM_SILENT_COMMUNICATION)), BSWM_COMM_CURRENTMODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_COMM_CURRENTMODE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
#endif
  
  BswM_ComM_OldState[Network] = BswM_ComM_CurrentState[Network];
  
  BswM_ComM_CurrentState[Network] = RequestedMode;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_COMM_CHANNEL, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)RequestedMode);
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */




/*********************************************************************************************************************/
/*! \brief      Function called by ComM to indicate the current communication mode of a PNC.
*   \param[in]  Network      : The PNC that the indicated state corresponds to.
*   \param[in]  RequestedMode: The current state of the PNC
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_ComM_CurrentPNCMode(PNCHandleType Pnc, ComM_PncModeType RequestedMode)
{
#if defined (BSWM_PN_ENABLED)
# if (BSWM_PN_ENABLED == STD_OFF)
#  if (V_USE_DUMMY_STATEMENT == STD_ON)
  (void)Pnc; /* PRQA S 3112 */ /* MD_BswM_3112 */
  (void)RequestedMode; /* PRQA S 3112 */ /* MD_BswM_3112 */
#  endif
# else
  BswM_UserType i;
  BswM_UserType userIndex = (BswM_UserType)0xFFu;
  uint8 pncLocalIndex = (uint8)0;

#  if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_COMM_CURRENT_PNC_MODE_ID, BSWM_E_NO_INIT);
  BswM_Det_ReportErrorReturn(((RequestedMode == COMM_PNC_REQUESTED) || (RequestedMode == COMM_PNC_READY_SLEEP) || (RequestedMode == COMM_PNC_PREPARE_SLEEP) || (RequestedMode == COMM_PNC_NO_COMMUNICATION)), BSWM_COMM_CURRENT_PNC_MODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
#  endif
  
  for(i = 0; i < BSWM_USER_COUNT; i ++)
  {
    if( BswM_UserConfig[i].domain == BSWM_DOMAIN_COMM_PNC )
    {
      if( BswM_UserConfig[i].pncGobalIndex == Pnc )
      {
        userIndex = i;
        break;
      }
      pncLocalIndex++;
    }
  }

  if( userIndex != (BswM_UserType)0xFFu )
  {
    /* PNC in configuration found, store previous and new state: */
    BswM_PreviousPncState[pncLocalIndex] = BswM_CurrentPncState[pncLocalIndex];
    BswM_CurrentPncState[pncLocalIndex] = RequestedMode;

    (void)BswM_RequestMode(userIndex, (BswM_ModeType)RequestedMode);
  }
# endif
#else
# if (V_USE_DUMMY_STATEMENT == STD_ON)
  (void)Pnc; /* PRQA S 3112 */ /* MD_BswM_3112 */
  (void)RequestedMode; /* PRQA S 3112 */ /* MD_BswM_3112 */
# endif
#endif
}/* PRQA S 2006 */ /* MD_BswM_2006 */



#if ( BSWM_ENABLE_DCM_COMTRL == STD_ON )
/**********************************************************************************************************************/
/*! \brief      Function called by DCM to request communication modes.
*   \param[in]  Network      : The communication channel that the diagnostic mode corresponds to
*   \param[in]  RequestedMode: The requested diagnostic communication mode.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_RequestCommunicationMode(NetworkHandleType Network, Dcm_CommunicationModeType RequestedMode)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_DCM_REQUESTCOMMUNICATIONMODE_ID, BSWM_E_NO_INIT);
  BswM_Det_ReportErrorReturn(
  ( 
    (RequestedMode == DCM_ENABLE_RX_TX_NORM)            || 
    (RequestedMode == DCM_ENABLE_RX_DISABLE_TX_NORM)    ||
    (RequestedMode == DCM_DISABLE_RX_ENABLE_TX_NORM)    || 
    (RequestedMode == DCM_DISABLE_RX_TX_NORMAL)         || 
    (RequestedMode == DCM_ENABLE_RX_TX_NORM_NM)         || 
    (RequestedMode == DCM_ENABLE_RX_DISABLE_TX_NORM_NM) || 
    (RequestedMode == DCM_DISABLE_RX_ENABLE_TX_NORM_NM) || 
    (RequestedMode == DCM_DISABLE_RX_TX_NORM_NM)        || 
    (RequestedMode == DCM_ENABLE_RX_TX_NM)              || 
    (RequestedMode == DCM_ENABLE_RX_DISABLE_TX_NM)      || 
    (RequestedMode == DCM_DISABLE_RX_ENABLE_TX_NM)      || 
    (RequestedMode == DCM_DISABLE_RX_TX_NM)
   ), BSWM_DCM_REQUESTCOMMUNICATIONMODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_DCM_REQUESTCOMMUNICATIONMODE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
# endif

  BswM_CurrentComCtrlState[Network] = RequestedMode;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_DCM_COMCTRL_CHANNEL, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)RequestedMode);
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif


#if ( BSWM_ENABLE_DCM_RESET == STD_ON )
/**********************************************************************************************************************/
/*! \brief      Function called by DCM to request a reset of the ECU.
*   \param[in]  RequestedMode: The requested DCM reset mode.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_RequestResetMode(Dcm_ResetModeType RequestedMode)
{
  BswM_UserType i;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_DCM_REQUESTRESETMODE_ID, BSWM_E_NO_INIT);

#  if ( BSWM_ENABLE_DCM_RESET_EXECUTION == STD_ON )
  BswM_Det_ReportErrorReturn(
  ( 
    (RequestedMode == DCM_NO_RESET)                           || 
    (RequestedMode == DCM_HARD_RESET)                         ||
    (RequestedMode == DCM_KEY_ON_OFF_RESET)                   || 
    (RequestedMode == DCM_SOFT_RESET)                         || 
    (RequestedMode == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET)  || 
    (RequestedMode == DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET) || 
    (RequestedMode == DCM_BOOTLOADER_RESET)                   || 
    (RequestedMode == DCM_RESET_EXECUTION)
   ), BSWM_DCM_REQUESTRESETMODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
#  else
  BswM_Det_ReportErrorReturn(
  ( 
    (RequestedMode == DCM_NO_RESET)                           || 
    (RequestedMode == DCM_HARD_RESET)                         ||
    (RequestedMode == DCM_KEY_ON_OFF_RESET)                   || 
    (RequestedMode == DCM_SOFT_RESET)                         || 
    (RequestedMode == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET)  || 
    (RequestedMode == DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET) || 
    (RequestedMode == DCM_BOOTLOADER_RESET)
   ), BSWM_DCM_REQUESTRESETMODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
#  endif
# endif
# if (BSWM_ENABLE_DCM_RESET_EXECUTION == STD_ON)
  if( RequestedMode != DCM_RESET_EXECUTION )
# endif
  {
    BswM_DcmResetMode = RequestedMode;
  }
# if (BSWM_ENABLE_DCM_RESET_EXECUTION == STD_ON)
  else
# endif
  {
    for(i = 0; i < BSWM_USER_COUNT;i ++)
    {
      if( BswM_UserConfig[i].domain == BSWM_DOMAIN_DCM_RESET )
      {
        (void)BswM_RequestMode(i, (BswM_ModeType) RequestedMode);
        break;
      }
    }
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif

#if ( BSWM_ENABLE_DCM_PASSIVE_MODE == STD_ON )
/**********************************************************************************************************************/
/*! \brief      Function called by DCM to set/reset the passive mode the ECU.
*   \param[in]  RequestedMode: The requested DCM reset mode.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_SetPassiveMode(boolean mode) 
{
# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_DCM_SET_PASSIVE_MODE_ID, BSWM_E_NO_INIT);
  BswM_Det_ReportErrorReturn(((mode == TRUE) || (mode == FALSE)), BSWM_DCM_SET_PASSIVE_MODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
# else
#  if( (BSWM_ENABLE_CAN_PASSIVE_MODE == STD_OFF) && (BSWM_ENABLE_CAN_PASSIVE_MODE == STD_OFF))
  (void)mode; /* PRQA S 3112 */ /* MD_BswM_3112 */
#  endif
# endif

# if(BSWM_ENABLE_CAN_PASSIVE_MODE == STD_ON)
  CanSM_SetEcuPassive(mode);
# endif

# if(BSWM_ENABLE_FR_PASSIVE_MODE == STD_ON)
  FrSM_SetEcuPassive(mode);
# endif
} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif

#if ( BSWM_ENABLE_DCM_APPL_UPDATE == STD_ON )
/**********************************************************************************************************************/
/*! \brief      Function called by DCM to inform about an updated application.
*   \param[in]  None
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Dcm_ApplicationUpdated(void) 
{
# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_DCM_APPLICATION_UPDATED_ID, BSWM_E_NO_INIT);
# endif

  BswM_ApplUpdateRequest = TRUE;


} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif

#if (BSWM_ENABLE_CANSM == STD_ON)
/**********************************************************************************************************************/
/*! \brief      Function called by CanSM to indicate its current state.
*   \param[in]  Network     : The CAN channel that the indicated state corresponds to.
*   \param[in]  CurrentState: The current state of the CAN channel.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_CanSM_CurrentState(NetworkHandleType Network, CanSM_BswMCurrentStateType CurrentState)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_CANSM_CURRENTSTATE_ID, BSWM_E_NO_INIT);

  BswM_Det_ReportErrorReturn(
  ( 
    (CurrentState == CANSM_BSWM_NO_COMMUNICATION)     || 
    (CurrentState == CANSM_BSWM_SILENT_COMMUNICATION) ||
    (CurrentState == CANSM_BSWM_FULL_COMMUNICATION)   || 
    (CurrentState == CANSM_BSWM_BUS_OFF)
   ), BSWM_CANSM_CURRENTSTATE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);

  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_CANSM_CURRENTSTATE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
# endif

  BswM_BusSM_OldState[Network] = BswM_BusSM_CurrentState[Network];

  BswM_BusSM_CurrentState[Network] = (BswM_BusSM_StateType)CurrentState;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_CANSM_CHANNEL, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)CurrentState);
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif

#if (BSWM_ENABLE_FRSM == STD_ON)
/**********************************************************************************************************************/
/*! \brief      Function called by FrSM to indicate its current state.
*   \param[in]  Network     : The FlexRay cluster that the indicated state corresponds to.
*   \param[in]  CurrentState: The corrent state of the FlexRay cluster
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context   
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_FrSM_StateChangeNotification(NetworkHandleType Network, FrSM_BswM_StateType PreviousState, FrSM_BswM_StateType CurrentState)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_FRSM_CURRENTSTATE_ID, BSWM_E_NO_INIT);

  BswM_Det_ReportErrorReturn(
  ( 
    (PreviousState == FRSM_BSWM_READY)                      || 
    (PreviousState == FRSM_BSWM_READY_ECU_PASSIVE)          ||
    (PreviousState == FRSM_BSWM_STARTUP)                    || 
    (PreviousState == FRSM_BSWM_STARTUP_ECU_PASSIVE)        || 
    (PreviousState == FRSM_BSWM_WAKEUP)                     || 
    (PreviousState == FRSM_BSWM_WAKEUP_ECU_PASSIVE)         || 
    (PreviousState == FRSM_BSWM_HALT_REQ)                   || 
    (PreviousState == FRSM_BSWM_HALT_REQ_ECU_PASSIVE)       || 
    (PreviousState == FRSM_BSWM_KEYSLOT_ONLY)               || 
    (PreviousState == FRSM_BSWM_KEYSLOT_ONLY_ECU_PASSIVE)   || 
    (PreviousState == FRSM_BSWM_ONLINE)                     || 
    (PreviousState == FRSM_BSWM_ONLINE_ECU_PASSIVE)         ||        
    (PreviousState == FRSM_BSWM_ONLINE_PASSIVE)             ||
    (PreviousState == FRSM_BSWM_ONLINE_PASSIVE_ECU_PASSIVE)
  ), BSWM_FRSM_CURRENTSTATE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);

  BswM_Det_ReportErrorReturn(
  ( 
    (CurrentState == FRSM_BSWM_READY)                      || 
    (CurrentState == FRSM_BSWM_READY_ECU_PASSIVE)          ||
    (CurrentState == FRSM_BSWM_STARTUP)                    || 
    (CurrentState == FRSM_BSWM_STARTUP_ECU_PASSIVE)        || 
    (CurrentState == FRSM_BSWM_WAKEUP)                     || 
    (CurrentState == FRSM_BSWM_WAKEUP_ECU_PASSIVE)         || 
    (CurrentState == FRSM_BSWM_HALT_REQ)                   || 
    (CurrentState == FRSM_BSWM_HALT_REQ_ECU_PASSIVE)       || 
    (CurrentState == FRSM_BSWM_KEYSLOT_ONLY)               || 
    (CurrentState == FRSM_BSWM_KEYSLOT_ONLY_ECU_PASSIVE)   || 
    (CurrentState == FRSM_BSWM_ONLINE)                     || 
    (CurrentState == FRSM_BSWM_ONLINE_ECU_PASSIVE)         ||        
    (CurrentState == FRSM_BSWM_ONLINE_PASSIVE)             ||
    (CurrentState == FRSM_BSWM_ONLINE_PASSIVE_ECU_PASSIVE)
  ), BSWM_FRSM_CURRENTSTATE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_FRSM_CURRENTSTATE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
# endif

  BswM_BusSM_OldState[Network] = (BswM_BusSM_StateType)PreviousState;

  BswM_BusSM_CurrentState[Network] = (BswM_BusSM_StateType)CurrentState;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_FRSM_CHANNEL, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)CurrentState);
  }
} /* PRQA S 2006, 6010 */ /* MD_BswM_2006, MD_MSR_STPTH */
#endif

#if ( BSWM_ENABLE_LINSM == STD_ON )
/**********************************************************************************************************************/
/*! \brief      Function called by LinSM to indicate its current state.
*   \param[in]  Network     : The LIN channel that the indicated state corresponds to.
*   \param[in]  CurrentState: The current state of the LIN channel.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_LinSM_CurrentState(NetworkHandleType Network, LinSM_ModeType CurrentState)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_LINSM_CURRENTSTATE_ID, BSWM_E_NO_INIT);

  BswM_Det_ReportErrorReturn(
  ( 
    (CurrentState == LINSM_BSWM_FULL_COM)     || 
    (CurrentState == LINSM_BSWM_NO_COM)       || 
    (CurrentState == LINSM_BSWM_RUN_SCHEDULE) ||        
    (CurrentState == LINSM_BSWM_GOTO_SLEEP)   
  ), BSWM_LINSM_CURRENTSTATE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_LINSM_CURRENTSTATE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
# endif

  BswM_BusSM_OldState[Network] = BswM_BusSM_CurrentState[Network];

  BswM_BusSM_CurrentState[Network] = (BswM_BusSM_StateType)CurrentState;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_LINSM_CHANNEL, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)CurrentState);
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */



/**********************************************************************************************************************/
/*! \brief      Function called by LinSM to indicate the currently active schedule table for a specific LIN channel.
*   \param[in]  Network        : The LIN channel that the schedule table switch have occurred on.
*   \param[in]  CurrentSchedule: The currently active schedule table of the LIN channel.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_LinSM_CurrentSchedule(NetworkHandleType Network, LinIf_SchHandleType CurrentSchedule)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_LINSM_CURRENTSCHEDULE_ID, BSWM_E_NO_INIT);
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_LINSM_CURRENTSCHEDULE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
  BswM_Det_ReportErrorReturn((CurrentSchedule < BswM_NrOfLinSchedules[Network]), BSWM_LINSM_CURRENTSCHEDULE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
# endif

  BswM_CurrentLinSchedule[Network] = CurrentSchedule;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_LINSM_SCHED, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)CurrentSchedule);
  }
}/* PRQA S 2006 */ /* MD_BswM_2006 */

/**********************************************************************************************************************/
/*! \brief      Function called by LinSM to indicate the end of a schedule table.
*   \param[in]  Network: index of the LIN network.
*   \param[in]  Schedule: index of the schedule table.
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_LinSM_ScheduleEnd_Notification(NetworkHandleType Network, LinIf_SchHandleType Schedule)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_LINSM_SCHEDEND_NOTIFICATION_ID, BSWM_E_NO_INIT);
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_LINSM_SCHEDEND_NOTIFICATION_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
  BswM_Det_ReportErrorReturn((Schedule < BswM_NrOfLinSchedules[Network]), BSWM_LINSM_SCHEDEND_NOTIFICATION_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
# endif

  BswM_LinScheduleEnd[Network] = (LinIf_SchHandleType)(Schedule + 1u);  /* ESCAN00062295 */

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_LINSM_SCHED_END, Network);

  if(localUserHandle != BSWM_USER_COMPARE_VALUE)
  { 
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)Schedule);
  }

  BswM_LinScheduleEnd[Network] = 0u;
}/* PRQA S 2006 */ /* MD_BswM_2006 */
#endif

#if (BSWM_ENABLE_LINTP == STD_ON)
/**********************************************************************************************************************/
/*! \brief      Function called by LinTP to request a mode for the corresponding LIN channel. The LinTp_Mode mainly 
*               correlates to the LIN schedule table that should be used.
*   \param[in]  Network           : The LIN channel that the LinTp mode request relates to.
*   \param[in]  LinTpRequestedMode: The requested LIN TP mode
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_LinTp_RequestMode(NetworkHandleType Network, LinTp_ModeType LinTpRequestedMode)
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_LINTP_REQUESTMODE_ID, BSWM_E_NO_INIT);

  BswM_Det_ReportErrorReturn(
  ( 
    (LinTpRequestedMode == LINTP_APPLICATIVE_SCHEDULE) || 
    (LinTpRequestedMode == LINTP_DIAG_REQUEST) || 
    (LinTpRequestedMode == LINTP_DIAG_RESPONSE) 
  ), BSWM_LINTP_REQUESTMODE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  
  BswM_Det_ReportErrorReturn((Network < BSWM_CHANNEL_COUNT), BSWM_LINTP_REQUESTMODE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
# endif

  BswM_LinTp_Mode[Network] = LinTpRequestedMode;

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_LINTP_CHANNEL, Network);

  if( localUserHandle != BSWM_USER_COMPARE_VALUE )
  {
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)LinTpRequestedMode);
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif



#if ( BSWM_ENABLE_NM == STD_ON )
/**********************************************************************************************************************/
/*! \brief      Function called by NM.
*   \param[in]  nmChannelHandle, nmPreviousState, nmCurrentState
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    
*   \note       
***********************************************************************************************************************/
FUNC( void, BSWM_CODE ) BswM_Nm_StateChangeNotification( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONST( Nm_StateType, AUTOMATIC) nmPreviousState, CONST( Nm_StateType, AUTOMATIC ) nmCurrentState )
{
  BswM_UserType localUserHandle;

# if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_NM_STATE_CHANGE_ID, BSWM_E_NO_INIT);

  BswM_Det_ReportErrorReturn(
  ( 
    (nmPreviousState == NM_STATE_BUS_SLEEP) || 
    (nmPreviousState == NM_STATE_PREPARE_BUS_SLEEP) || 
    (nmPreviousState == NM_STATE_READY_SLEEP) || 
    (nmPreviousState == NM_STATE_NORMAL_OPERATION)|| 
    (nmPreviousState == NM_STATE_REPEAT_MESSAGE) || 
    (nmPreviousState == NM_STATE_SYNCHRONIZE) || 
    (nmPreviousState == NM_STATE_WAIT_CHECK_ACTIVATION) || 
    (nmPreviousState == NM_STATE_WAIT_NETWORK_STARTUP) || 
    (nmPreviousState == NM_STATE_NORMAL_OPERATION) ||
    (nmPreviousState == NM_STATE_BUS_OFF)
  ), BSWM_NM_STATE_CHANGE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  
  BswM_Det_ReportErrorReturn(
  (
    (nmCurrentState == NM_STATE_BUS_SLEEP) || 
    (nmCurrentState == NM_STATE_PREPARE_BUS_SLEEP) || 
    (nmCurrentState == NM_STATE_READY_SLEEP) || 
    (nmCurrentState == NM_STATE_NORMAL_OPERATION)|| 
    (nmCurrentState == NM_STATE_REPEAT_MESSAGE) || 
    (nmCurrentState == NM_STATE_SYNCHRONIZE) || 
    (nmCurrentState == NM_STATE_WAIT_CHECK_ACTIVATION) || 
    (nmCurrentState == NM_STATE_WAIT_NETWORK_STARTUP) || 
    (nmCurrentState == NM_STATE_NORMAL_OPERATION) || 
    (nmCurrentState == NM_STATE_BUS_OFF)
  ), BSWM_NM_STATE_CHANGE_ID, BSWM_E_REQ_MODE_OUT_OF_RANGE);
  
  BswM_Det_ReportErrorReturn((nmChannelHandle < BSWM_CHANNEL_COUNT), BSWM_NM_STATE_CHANGE_ID, BSWM_E_REQ_USER_OUT_OF_RANGE);
# endif

  localUserHandle = BswM_GetUserHandle(BSWM_DOMAIN_NM_CHANNEL, nmChannelHandle);

  BswM_Nm_CurrentState[nmChannelHandle] = nmCurrentState;
  BswM_Nm_OldState[nmChannelHandle] = nmPreviousState;

  if( localUserHandle != BSWM_USER_COMPARE_VALUE )
  {
    (void)BswM_RequestMode(localUserHandle, (BswM_ModeType)nmCurrentState);
  }
} /* PRQA S 2006 */ /* MD_BswM_2006 */
#endif


/**********************************************************************************************************************/
/*! \brief      Main function of the BswM
*   \param[in]  None
*   \param[out] None
*   \return     None
*   \pre        BswM was initialized
*   \context    Task context
*   \note       
***********************************************************************************************************************/
FUNC(void, BSWM_CODE) BswM_MainFunction(void)
{
  BswM_UserType requesting_user;
  uint8 ruleIndex;
  uint8 localSemaphore;
  BswM_RuleTableFctPtrType pRuleFct = NULL_PTR;
  P2CONST(BswM_UserConfigType, AUTOMATIC, BSWM_CONST) pBswM_UserConfig;

#if(BSWM_DEV_ERROR_DETECT == STD_ON)
  BswM_Det_ReportErrorReturn((BSWM_INIT == BswM_InitStatus), BSWM_MAINFUNCTION_ID, BSWM_E_NO_INIT);
#endif

  BswM_EnterCriticalArea(0);
  localSemaphore = BswM_QueueSemaphore;
  if(BswM_QueueSemaphore == BSWM_REQUEST_SEMAPHORE_UNLOCKED)
  { 
    BswM_QueueSemaphore = BSWM_REQUEST_SEMAPHORE_LOCKED;
  } 

#if (BSWM_ENABLE_TMR == STD_ON)
  for(requesting_user = 0; requesting_user < BSWM_TIMER_COUNT; requesting_user++)
  {
    if(BswM_Timer[requesting_user] > 0u)
    {
      BswM_Timer[requesting_user] --;
      if(BswM_Timer[requesting_user]  == 0u)
      {
        BswM_TimerState[requesting_user] = BSWM_TMR_EXPIRED;
      }
    }
  }
#endif

  BswM_LeaveCriticalArea(0);


#if (BSWM_ENABLE_DCM_APPL_UPDATE == STD_ON)
  if(BswM_ApplUpdateRequest == TRUE)
  {
# if(BSWM_ENABLE_DCM_APPL_UPDATE_RTE == STD_ON )
    BSWM_RTE_MODE_FCT_NAME(RTE_MODE_BswMMode_APPLICATION_UPDATED);
# else
    Appl_BswM_ApplicationUpdated();
# endif
    BswM_ApplUpdateRequest = FALSE;
  }
#endif


  for(requesting_user = 0; requesting_user < BSWM_USER_COUNT; requesting_user++)
  {
    pBswM_UserConfig = (P2CONST(BswM_UserConfigType, AUTOMATIC, BSWM_CONST))(&BswM_UserConfig[requesting_user]);
    if(BSWM_RULE_DEFERRED == pBswM_UserConfig->modeExecContext)
    {
      for( ruleIndex = 0; ruleIndex < pBswM_UserConfig->NrOfRules; ruleIndex++ )
      {
        if( pRuleFct != pBswM_UserConfig->RuleFctPtr[ruleIndex] )
        {
          pRuleFct = pBswM_UserConfig->RuleFctPtr[ruleIndex];
          if(NULL_PTR != pRuleFct)
          { 
            (void)pRuleFct();
          }
        }
      }
    } 
  }

  if(BSWM_REQUEST_SEMAPHORE_UNLOCKED == localSemaphore)
  {
    /* Immediately process other pending immediate requests */
    BswM_ProcessQueuedRequests();

    /* Unlock semaphore AFTER processing of the queue */
    BswM_QueueSemaphore = BSWM_REQUEST_SEMAPHORE_UNLOCKED;
  }
#if(BSWM_MODE_NOTIFICATION == STD_ON)
  BswM_ModeNotificationFct();
#endif
  
} /* PRQA S 2006, 6010, 6030, 6080 */ /* MD_BswM_2006, MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STMIF */


#define BSWM_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


/* module specific MISRA deviations:

 MD_BswM_0779:
      Reason:     Identifier does not differ from other identifiers within 31 significant characters.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Covered by code review.

 MD_BswM_3112:
      Reason:     Dummy statement to avoid compiler warnings.
      Risk:       There is no risk as such statements have no effect on the code.
      Prevention: Covered by code review.

 MD_BswM_2006:
      Reason:     Function has more than one return path.
      Risk:       no risk, an error is reported in this case.
      Prevention: use correct versions. 

 MD_BswM_3453:
      Reason:     Function-like macro.
      Risk:       no risk, to use a function makes no sense in this case.
      Prevention: Cobered by code review. 
*/

/**********************************************************************************************************************
 *  END OF FILE: BswM.c
 *********************************************************************************************************************/
