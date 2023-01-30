/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2006-2014 by Vector Informatik GmbH, all rights reserved
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  EcuM.h
 *    Component:  SysService_AsrEcuM
 *       Module:  EcuM
 *    Generator:  -
 *
 *  Description:  The ECU State Manager is responsible for
 *                  - initialization of the entire BSW Modules (including OS and RTE
 *                  - configuration of the entire ECU for sleep mode
 *                  - fast and systematic wakeup behavior
 *                  - shutdown of the ECU
 *
 *                To be very independent of different system designs e.g. different Modules to initialize,
 *                external/internal Watchdog, etc., the ECU State Manager provides over a mechanism named "callouts"
 *                a way to adapt the startup and shutdown behavior. The system designer must fill the proper code into
 *                the callouts.
 *********************************************************************************************************************/
 
/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Christian Marchl              Chm           Vector Informatik GmbH
 *  Bethina Mausz                 Bmz           Vector Informatik GmbH
 *  Martin Froschhammer           Mfr           Vector Informatik GmbH
 *  Philipp Ritter                Rpp           Vector Informatik GmbH
 *  Jochen Vorreiter              Vjn           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  03.00.01  2007-09-17  Chm     ESCAN00022372 Quality assurance activities necessary for Component
 *                                              SysService_EcuM
 *  03.00.02  2007-12-05  Chm     ESCAN00023500 No changes here
 *                                ESCAN00023529 No changes here
 *                                ESCAN00022623 Implemented EcuM_GetStateWrapper() as function
 *  04.00.00  2008-03-03  Chm     ESCAN00022498 No changes here
 *  04.00.01  2008-04-17  Chm     ESCAN00026230 No changes here
 *                                -             Added EcuM_GetStateWrapper()
 *                                ESCAN00026333 No changes here
 *  04.01.00  2008-05-15  Chm     -             Added ASR 2.1 compatibility switches around declaration of functions
 *                                              EcuM_SetWakeupEvent() and EcuM_ValidateWakeupEvent()
 *  04.01.01  2008-06-06  Chm     ESCAN00027458 No changes here
 *  04.01.02  2008-06-16  Chm     -             No changes here
 *  04.02.00  2008-06-26  Chm     ESCAN00027917 No changes here
 *                                ESCAN00027637 No changes here
 *                                ESCAN00026668 No changes here
 *  04.03.00  2008-07-15  Chm     ESCAN00028254 No changes here
 *                                ESCAN00028366 Added support for customized ComM according to ASR 2.1
 *  04.03.01  2008-09-24  Chm     ESCAN00030196 Added support for EcuM_GetState() API according to ASR 2.1
 *                                ESCAN00029718 Added preprocessor switch for CANOE
 *  04.04.00  2008-10-22  Chm     ESCAN00030470 Added PreCompile Variant support
 *  05.00.00  2008-11-28  Chm     ESCAN00031236 Added EcuM_PrivateCfg.h include
 *                                ESCAN00030956 Added mode management support
 *                                ESCAN00030909 Added boottarget selection through callouts
 *                                ESCAN00030031 Added transition from startup to wakeup validation state
 *                                ESCAN00029870 No changes here
 *  05.00.01  2009-02-18  Chm     ESCAN00031908 No changes here
 *            2009-02-19  Chm     ESCAN00032309 No changes here
 *            2009-02-23  Chm     ESCAN00030139 Added ECUM_E_GENERATOR_COMPATIBILITY error code
 *            2009-02-25  Chm     ESCAN00031790 No changes here
 *            2009-03-10  Chm     ESCAN00033728 No changes here
 *            2009-03-16  Chm     ESCAN00033852 No changes here
 *  05.01.00  2009-05-15  Chm     ESCAN00035148 Add support for vendor specific parameter to support multiple identity ECUs support
 *  05.02.00  2009-07-14  Chm     ESCAN00035006 No changes here
 *            2009-07-14  Chm     ESCAN00033852 No changes here
 *            2009-07-14  Chm     ESCAN00035914 No changes here
 *            2009-07-15  Chm     ESCAN00035987 No changes here 
 *            2009-07-15  Chm     ESCAN00034791 No changes here 
 *            2009-07-15  Chm     ESCAN00034696 No changes here
 *            2009-07-15  Chm     ESCAN00036111 No changes here
 *            2009-07-17  Chm     ESCAN00036325 No changes here
 *            2009-07-21  Chm     ESCAN00036576 No changes here
 *  05.02.01  2009-11-24  Chm     ESCAN00039346 No changes here
 *  05.02.02  2009-12-11  Chm     ESCAN00039057 No changes here
 *            2009-12-11  Chm     ESCAN00039414 No changes here
 *            2009-12-15  Chm     ESCAN00039778 No changes here
 *  05.02.03  2010-04-14  Chm     ESCAN00042313 Added error code 'ECUM_E_EXTENDED_LIB_VERSION_CHECK_FAILED', added service id 'ECUM_SID_DRIVER_INIT_ZERO'
 *            2010-04-24  Chm     ESCAN00041361 No changes here
 *            2010-04-24  Chm     ESCAN00042504 No changes here
 *  05.02.04  2010-07-29  Bmz     ESCAN00043949 No changes here
 *  05.02.05  2010-09-21  Bmz     ESCAN00045256 Version update
 *  05.03.00  2010-10-18  Bmz     ESCAN00044913 EcuM_PreMcuSetModeHook and EcuM_PostMcuSetModeHook replaced by a callout
 *  05.05.00  2010-11-12  Bmz     ESCAN00045114 Add a new transition for ECUM_INT_STATE_WAKEUP_REACTION
 *            2010-11-18  Bmz     ESCAN00046994 No changes here
 *            2010-11-24  Bmz     ESCAN00046158 No changes here
 *  05.05.01  2011-02-15  Bmz     ESCAN00048574 No changes here
 *  05.06.00  2011-04-06  Bmz     ESCAN00048423 SW version update
 *                                ESCAN00049111 No changes here
 *  06.00.00  2011-04-26  Bmz     ESCAN00049994 SW version update
 *                                ESCAN00046958 No changes here
 *                                ESCAN00051179 No changes here
 *                                ESCAN00051192 No changes here
 *                                ESCAN00051407 No changes here
 *                                ESCAN00052144 No changes here
 *                                ESCAN00052248 SWC-D shall be generated according to AUTOSAR Schema 3.2.1 (Mj-Nr Update)
 *  07.00.00  2011-09-20  Bmz     ESCAN00053281 update MISRA justifications
 *                                ESCAN00052193 Add call of EcuM_ErrorHook call-back
 *                                ESCAN00046525 No changes here
 *                                ESCAN00052958 changed AppModeType into EcuM_AppModeType
 *                                ESCAN00052498 EcuM shall abort waiting of pending NvM job (NvM_WriteAll)
 *                                ESCAN00054279 No changes here
 *                                -             add NULL_PTR checks in (EcuMS.C) TTII protocol, to ensure valid array access
 *            2011-12-14  Mfr     ESCAN00054338 Function declation for EcuM_InternalCheckWakeup added
 * 07.00.01   2012-02-22  Rpp     ESCAN00056464 No changes here
 *                                ESCAN00056481 No changes here
 * 07.01.00   2012-03-15  Rpp     ESCAN00057625 ASR2.1 parts removed
 * 07.02.00   2012-04-11  Rpp     ESCAN00057480 ECUM_E_INCONSISTENT_CONFIGURATION renamed to ECUM_E_HOOK_INCONSISTENT_CONFIGURATION
 *                                              ECUM_E_RAM_CHECK_FAILED renamed to ECUM_E_HOOK_RAM_CHECK_FAILED
 *                                ESCAN00034634 No changes here
 *                                ESCAN00058011 No changes here
 *                                ESCAN00058236 Include EcuM_Cbk.h instead of EcuM_Generated_Types.h and EcuM_Cfg.h
 * 07.03.00   2012-06-23  Rpp     ESCAN00058682 No changes here
 *                                ESCAN00058706 No changes here
 *                                ESCAN00058798 No changes here
 *                                ESCAN00059001 No changes here
 * 07.04.00   2012-08-28  Vjn     ESCAN00060104 Function declaration for EcuM_StartCheckWakup and EcuM_EndCheckWakeup added
 * 07.04.01   2012-10-17  Vjn     ESCAN00062161 No changes here
 * 07.04.02   2013-01-03  Vjn     ESCAN00062152 No changes here
 * 07.04.03   2013-01-23  Vjn     ESCAN00063377 No changes here
 * 07.05.00   2013-04-08  Vjn     ESCAN00060532 No changes here
 *                                ESCAN00060532 No changes here
 *                                ESCAN00064097 No changes here
 *                                ESCAN00066763 No changes here
 *                                ESCAN00067041 Added ECUM_E_RTE_CURRENT_MODE_PORT_UNCONNECTED and ECUM_SID_RTE_WAIT_ON_FEEDBACK_EVENT
 * 07.05.01   2013-07-15  Vjn     ESCAN00068962 No changes here
 *                                ESCAN00067950 No changes here
 * 07.05.02   2013-07-31  Vjn     ESCAN00069420 No changes here
 * 07.05.03   2013-09-30  Vjn     ESCAN00069451 No changes here
 * 07.06.00   2013-10-07  Vjn     ESCAN00070295 No changes here
 *                                ESCAN00071022 No changes here
 *                                ESCAN00068876 No changes here
 *                                ESCAN00071394 No changes here
 *                                ESCAN00071404 No changes here
 *                                ESCAN00071833 No changes here
 * 07.06.01   2014-01-30  Vjn     ESCAN00073055 No changes here
 *                                ESCAN00073054 No changes here
 *                                ESCAN00073306 No changes here
 *                                ESCAN00073908 No changes here
 *********************************************************************************************************************/

/* ---- Protection against multiple inclusion ----------------------------- */
#if (!defined ECUM_H)
# define ECUM_H

/*---- Version identification -  ---*/
# define ECUM_VENDOR_ID                                               (30u)   /* Vector Informatik GmbH */
# define ECUM_MODULE_ID                                               (10u)
# define ECUM_INSTANCE_ID                                             (0u)

/* ##V_CFG_MANAGEMENT ##CQProject : SysService_AsrEcuM CQComponent : Implementation */
# define SYSSERVICE_ASRECUM_VERSION                                   0x0706u
# define SYSSERVICE_ASRECUM_RELEASE_VERSION                           0x01u

# if (!defined ECUM_AR_MAJOR_VERSION)
#  define ECUM_AR_MAJOR_VERSION                                       (1u)
# endif
# if (!defined ECUM_AR_MINOR_VERSION)
#  define ECUM_AR_MINOR_VERSION                                       (2u)
# endif
# if (!defined ECUM_AR_PATCH_VERSION)
#  define ECUM_AR_PATCH_VERSION                                       (0u)
# endif

# define ECUM_SW_MAJOR_VERSION                                        (SYSSERVICE_ASRECUM_VERSION >> 8u)
# define ECUM_SW_MINOR_VERSION                                        (SYSSERVICE_ASRECUM_VERSION & 0x00FFu)
# define ECUM_SW_PATCH_VERSION                                        SYSSERVICE_ASRECUM_RELEASE_VERSION

/* ----------Error Codes in Development-Mode------------------------------- */
# define ECUM_E_NOT_INITED                                            (0x10u)
# define ECUM_E_SERVICE_DISABLED                                      (0x11u)
# define ECUM_E_NULL_POINTER                                          (0x12u)
# define ECUM_E_INVALID_PAR                                           (0x13u)
# define ECUM_E_MULTIPLE_RUN_REQUESTS                                 (0x14u)
# define ECUM_E_MISMATCHED_RUN_RELEASE                                (0x15u)
# define ECUM_E_STATE_PAR_OUT_OF_RANGE                                (0x16u)
# define ECUM_E_UNKNOWN_WAKEUP_SOURCE                                 (0x17u)
# define ECUM_E_PARAM_VINFO                                           (0x18u)
/* Additional error codes not defined in SWS -------------------------------*/
# define ECUM_E_OS_NOT_STARTED_SUCCESFULLY                            (0x30u)
# define ECUM_E_WRONG_ECUM_USAGE                                      (0x31u)
# define ECUM_E_WAKEUP_VALIDATION_PROT_ERROR                          (0x32u)
# define ECUM_E_OFF_STATE_EXPECTED                                    (0x33u)
# define ECUM_E_MODULE_NOT_IN_RUN_STATE                               (0x34u)
# define ECUM_E_GENERATOR_COMPATIBILITY                               (0x35u)
# define ECUM_E_EXTENDED_LIB_VERSION_CHECK_FAILED                     (0x36u)
# define ECUM_E_RTE_CURRENT_MODE_PORT_UNCONNECTED                     (0x39u)
/* Additional error codes notified to EcuM_ErrorHook -----------------------*/
# define ECUM_E_HOOK_INCONSISTENT_CONFIGURATION                       (0x37u)
# define ECUM_E_HOOK_RAM_CHECK_FAILED                                 (0x38u)

/* ----------EcuM Service Identification----------------------------------- */
# define ECUM_SID_GET_VERSION_INFO                                    (0u)
# define ECUM_SID_INIT                                                (1u)
# define ECUM_SID_SHUTDOWN                                            (2u)
# define ECUM_SID_REQUEST_RUN                                         (3u)
# define ECUM_SID_RELEASE_RUN                                         (4u)
# define ECUM_SID_KILL_ALL_RUN_REQUESTS                               (5u)
# define ECUM_SID_SELECT_SHUTDOWN_TARGET                              (6u)
# define ECUM_SID_GET_STATE                                           (7u)
# define ECUM_SID_GET_LAST_SHUTDOWN_TARGET                            (8u)
# define ECUM_SID_GET_SHUTDOWN_TARGET                                 (9u)
# define ECUM_SID_REQUEST_POST_RUN                                    (10u)
# define ECUM_SID_RELEASE_POST_RUN                                    (11u)
# define ECUM_SID_SET_WAKEUP_EVENT                                    (12u)
# define ECUM_SID_GET_PENDING_WAKEUP_EVENTS                           (13u)
# define ECUM_SID_COMM_REQUEST_RUN                                    (14u)
# define ECUM_SID_SELECT_APPLICATION_MODE                             (15u)
# define ECUM_SID_COMM_RELEASE_RUN                                    (16u)
# define ECUM_SID_GET_APPLICATION_MODE                                (17u)
# define ECUM_SID_SELECT_BOOT_TARGET                                  (18u)
# define ECUM_SID_GET_BOOT_TARGET                                     (19u)
# define ECUM_SID_VALIDATE_WAKEUP_EVENT                               (20u)
# define ECUM_SID_GET_VALIDATED_WAKEUP_EVENTS                         (21u)
# define ECUM_SID_CLEAR_WAKEUP_EVENT                                  (22u)
# define ECUM_SID_GET_STATUS_OF_WAKEUP_SOURCE                         (23u)
# define ECUM_SID_MAIN_FUNCTION                                       (24u)
# define ECUM_SID_GET_EXPIRED_WAKEUP_EVENTS                           (25u)
# define ECUM_SID_STARTUP_TWO                                         (26u)
# define ECUM_SID_COMM_HAS_REQUESTED_RUN                              (27u)
# define ECUM_SID_START_CHECK_WAKEUP                                  (28u)
# define ECUM_SID_END_CHECK_WAKEUP                                    (29u)
# define ECUM_SID_CB_NFY_NVM_JOB_END                                  (101u)
# define ECUM_SID_RTE_WAIT_ON_FEEDBACK_EVENT                          (102u)
/* callout service IDs */
# define ECUM_SID_GENERATOR_COMPATIBILITY_ERROR                       (202u)
# define ECUM_SID_DRIVER_INIT_ZERO                                    (203u)

/* ---- API CFG Includes -------------------------------------------------- */
/* include of configuration public part */
#include "EcuM_Cbk.h"
/* ---- API Functions ----------------------------------------------------- */
# define ECUM_START_SEC_CODE
# include "MemMap.h"      /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(void, ECUM_API_CODE) EcuM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) versioninfo);

/* Initialization of the ECU State Manager */
FUNC(void, ECUM_API_CODE) EcuM_Init(void);

/* De-initialization of the ECU State Manager, should be called from
 * OS shutdown hook routine
 */
FUNC(void, ECUM_API_CODE) EcuM_Shutdown(void);

/* Requesting RUN state for this user */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_RequestRUN(EcuM_UserType User_t);

/* Release RUN state for this user */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ReleaseRUN(EcuM_UserType User_t);

/* Request POST RUN state for this user */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_RequestPOST_RUN(EcuM_UserType User_t);

/* Release POST RUN state for this user */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ReleasePOST_RUN(EcuM_UserType User_t);

/* Selects the Shutdown target for the next Shutdown */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_SelectShutdownTarget(EcuM_StateType EcuM_TargetState_t, uint8 sleepMode_u8);

/* Perform a Reset of the System, be careful  */
FUNC(void, ECUM_API_CODE) EcuM_KillAllRUNRequests(void);

/* Retrieve the actual internal ECUM state */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);

 /* Returns the current chosen Shutdown Target */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetShutdownTarget
(
    P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) Target_pt,
    P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)          SleepMode_pu8
);

/* Retrieve Information about the last ECU state from which the last
 * wakeup or power up occurred
 */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetLastShutdownTarget
(
    P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) ShutdownTarget_pt,
    P2VAR(uint8, AUTOMATIC, ECUM_APPL_DATA)          SleepMode_pu8
);

/* Declaration only for AUTOSAR 2.1 compatibility (in AUTOSAR 3.0 the declaration is located in EcuM_Cbk.h)*/
# if !defined (ECUM_VALIDATE_WAKEUP_EVENT_DECLARATION)
#  define ECUM_VALIDATE_WAKEUP_EVENT_DECLARATION
  FUNC(void, ECUM_CODE) EcuM_ValidateWakeupEvent(EcuM_WakeupSourceType WakeupSource_t);
# endif /* ECUM_VALIDATE_WAKEUP_EVENT_DECLARATION */

/* Declaration only for AUTOSAR 2.1 compatibility (in AUTOSAR 3.0 the declaration is located in EcuM_Cbk.h)*/
# if !defined (ECUM_SET_WAKEUP_EVENT_DECLARATION)
#  define ECUM_SET_WAKEUP_EVENT_DECLARATION
  FUNC(void, ECUM_CODE) EcuM_SetWakeupEvent(EcuM_WakeupSourceType WakeupSource_t);
# endif /* ECUM_SET_WAKEUP_EVENT_DECLARATION */

/* Returns information about a wakeup validation is in progress */
FUNC(EcuM_WakeupSourceType, ECUM_API_CODE)EcuM_GetPendingWakeupEvents(void);

/* Clear the wakeupevent for the denoted wakeupsource */
FUNC(void, ECUM_API_CODE) EcuM_ClearWakeupEvent(EcuM_WakeupSourceType WakeupSource_t);

/* Returns all successful validated wakeupevents from last startup (more than
 * one wakeupevents are possible due to COM channels
 */
FUNC(EcuM_WakeupSourceType, ECUM_API_CODE) EcuM_GetValidatedWakeupEvents(void);

/* Returns the Wakeupevents where validation was not successful */
FUNC(EcuM_WakeupSourceType, ECUM_API_CODE) EcuM_GetExpiredWakeupEvents(void);

/* Return the status of denoted wakeup source */
FUNC(EcuM_WakeupStatusType, ECUM_API_CODE) EcuM_GetStatusOfWakeupSource(EcuM_WakeupSourceType WakeupSources_t);

/* Set the application mode for the next restart */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_SelectApplicationMode(EcuM_AppModeType AppMode_t);

/* Returns the current selected application mode */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetApplicationMode(P2VAR(EcuM_AppModeType, AUTOMATIC, ECUM_APPL_DATA) AppMode_pt);

/* Wrapper functions for Applicationmode-Port of the ECUM */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_Rte_SelectApplicationMode(EcuM_AppModeType AppMode_t);

FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_Rte_GetApplicationMode
(
  P2VAR(EcuM_AppModeType, AUTOMATIC, ECUM_APPL_DATA) AppMode_pt
);
/* Returns the current selected boot target */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetBootTarget
(
  P2VAR(EcuM_BootTargetType, AUTOMATIC, ECUM_APPL_DATA) BootTarget_pt
);

/* set the boot target */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_SelectBootTarget(EcuM_BootTargetType BootTarget_t);

/* The service which implements all activities of the ECU state Manager
 * while OS is up and running.
 */
FUNC(void, ECUM_API_CODE) EcuM_MainFunction(void);

/* Implements the startup phase where the OS is running */
FUNC(void, ECUM_API_CODE) EcuM_StartupTwo(void);

/* Requesting RUN state for a communication channel */
#  if (( (ECUM_CONFIG_VARIANT == ECUM_VARIANT_PRECOMPILE) && (ECUM_INCLUDE_COMM == STD_ON) ) \
      || (ECUM_CONFIG_VARIANT != ECUM_VARIANT_PRECOMPILE) \
      || (STD_ON == ECUM_IDENTITY_MANAGER_CONFIG))

    /* Request RUN state for a communication channel */
    FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ComM_RequestRUN(NetworkHandleType channel);

    /* Release RUN state for a communication channel */
    FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ComM_ReleaseRUN(NetworkHandleType channel);

    /* Query function for the ComM to query the state of a communication channel */
    FUNC(boolean, ECUM_API_CODE) EcuM_ComM_HasRequestedRUN(NetworkHandleType channel);
#  else
#   define EcuM_ComM_RequestRUN(channel)
#   define EcuM_ComM_ReleaseRUN(channel)
#   define EcuM_ComM_HasRequestedRUN(channel)
#  endif

/* Internal functions Called from Ecum_Callout_Stubs */

/* EcuM internal processing for Ecum_CheckWakeup */
FUNC(void, ECUM_CODE) EcuM_StartCheckWakeup(EcuM_WakeupSourceType WakeupSource);

FUNC(void, ECUM_CODE) EcuM_EndCheckWakeup(EcuM_WakeupSourceType WakeupSource);

/* Wrapper function of function EcuM_GetState(). Needed for service ports */
FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetStateWrapper
(
  EcuM_UserType user_t,
  P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state_pt
);

# define ECUM_STOP_SEC_CODE
# include "MemMap.h"      /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* #if (!defined ECUM_H) */
/**********************************************************************************************************************
 *  END OF FILE: ECUM.H
 *********************************************************************************************************************/
