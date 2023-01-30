/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name
 *    WdgM.h
 *
 * Purpose
 *   Main header file for Watchdog Manager Module
 *
 * Revisions
 *
 *   11-Oct-2010  (PPU) Creation
 *   21-Jul-2011  (PPU) [41408] Entity Deactivation/Activation added
 *   05-Sep-2011  (PPU) [42340] for safety reasons use the primary reset path
 *                              for IMMEDIATE_RESET
 *   13-Mar-2012  (PPU) [45210] Hardware TickCounter implemented
 *   20-Apr-2012  (PPU) [45700] Trigger Mode implemented
 *   07-Jul-2012  (VLE) [45827] AUTOSAR release version macros
 *   07-Aug-2012  (PPU) [47990] Added WdgM_SetMode(x) to 3_1 compatible functions
 *   13-Aug-2012  (VLE) [48167] AUTOSAR 3.1 compatibility function naming
 *   22-Aug-2012  (VLE) [46993] External modules Det, Dem, Mcu, BswM_WdgM
 *                              replaced by user-defined Appl_* modules
 *   28-Aug-2012  (VLE) [46820] Compiler abstraction according to AUTOSAR
 *   04-Sep-2012  (PPU) [48587] Formal review - change the version to 2.0.0
 */



/* -------------------------------------------------------------------------- */
/*                        GENERAL JUSTIFICATIONS                              */
/* -------------------------------------------------------------------------- */
/* Tracebility to UDD Checklist p. 6.1
 * Justification : The Traceability to UDD is given by clear and unique function
                   names, defines and parameters. The traceability to AUTOSAR is
                   done by using label WDGMxyz: what coresponds to the AUTOSAR
                   used specification                                         */
/* -------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                           */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:3458) Macro defines a braced code statement block.
                   MISRA-C:2004 Rule 19.4
 * Justification : The function 'WdgM_GetVersionInfo' is realised as a macro as
                   advised by AUTOSAR.                                        */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:3453) A function could probably be used instead of
                   this function-like macro.
                   MISRA-C:2004 Rule 19.7
 * Justification : The functions for reporting DEM and DET errors a realised as
                   macros to provide simple way to enable/disable them by a
                   preprocessor switch.                                       */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(3:3210) The global identifier 'WdgM_CheckpointReached' /
                   'WdgM_SetMode' / 'WdgM_GetLocalStatus' /
                   'WdgM_GetGlobalStatus' / 'WdgM_PerformReset' /
                   'WdgM_GetMode' / 'WdgM_DeactivateSupervisionEntity' /
                   'WdgM_ActivateSupervisionEntity' / 'WdgM_Init' /
                   'WdgM_UpdateTickCount' / 'WdgM_MainFunction' /
                   'WdgM_SetTickCount' / 'WdgM_GetTickCount' /
                   'WdgM_WriteGlobalActivityFlag' /
                   'WdgM_WriteGlobalTransitionFlag' /
                   'WdgM_ReadGlobalTransitionFlag' /
                   'GlobalSuspendInterrupts' / 'GlobalRestoreInterrupts'
                   is declared but is not used.
 * Justification : The function is the interface of this SW module to the upper
                   SW layers.                                                */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:3408) 'WdgM_CheckpointReached' /
                   'WdgM_SetMode' / 'WdgM_GetLocalStatus' /
                   'WdgM_GetGlobalStatus' / 'WdgM_PerformReset' /
                   'WdgM_GetMode' / 'WdgM_DeactivateSupervisionEntity' /
                   'WdgM_ActivateSupervisionEntity' / 'WdgM_Init' /
                   'WdgM_UpdateTickCount' / 'WdgM_MainFunction' /
                   'WdgM_SetTickCount' / 'WdgM_GetTickCount' /
                   'WdgM_WriteGlobalActivityFlag' /
                   'WdgM_WriteGlobalTransitionFlag' /
                   'WdgM_ReadGlobalTransitionFlag'
                   has external linkage but is being defined without any
                   previous declaration.
 * Justification : The function is the interface of this SW module to the upper
                   SW layers and is declared in this header file.            */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(4:3447) 'WdgM_WriteGlobalTransitionFlag' /
                   'WdgM_ReadGlobalTransitionFlag' has external linkage but this
                   declaration is not in a header file.
 * Justification : This file (WdgM.h) is a header file.                       */
/* -------------------------------------------------------------------------- */
/* Error Message : Msg(6:0288) [I] Source file 'WdgM.h' has comments containing
                   characters which are not members of the basic source
                   character set.
 * Justification : The (at) character is needed for doxygen comments.         */
/* PRQA S 0288 EOF */

#ifndef _WDGM_H_
#define _WDGM_H_

/* ****************************************************************************
 * Includes
 ******************************************************************************/
#include "WdgM_Cfg.h"

/* ****************************************************************************
 * Macros
 ******************************************************************************/

/* SW-configuration versions used for compatibility check */
#define WDGM_SW_MAJOR_VERSION  2
#define WDGM_SW_MINOR_VERSION  0
#define WDGM_SW_PATCH_VERSION  3

/* AUTOSAR release version */
#define WDGM_AR_MAJOR_VERSION 4
#define WDGM_AR_MINOR_VERSION 0
#define WDGM_AR_PATCH_VERSION 1

/* WdgM_Cfg.h version check */
#if !( (WDGM_SW_MAJOR_VERSION == WDGM_CFG_TYPES_HDR_MAJOR_VERSION) \
    && (WDGM_SW_MINOR_VERSION == WDGM_CFG_TYPES_HDR_MINOR_VERSION) \
    && (WDGM_SW_PATCH_VERSION == WDGM_CFG_TYPES_HDR_PATCH_VERSION) \
    )
    #error "Version mismatch. Incorrect version of WdgM_Cfg.h"
#endif

/* Module-ID for WDGM */
#define WDGM_VENDOR_ID                  46
#define WDGM_MODULE_ID                  13

/** API Service ID for WdgM_Init */
#define API_ID_WdgM_Init                0x00u

/** API Service ID for WdgM_CheckpointReached */
#define API_ID_WdgM_CheckpointReached   0x0eu

/** API Service ID for WdgM_GetVersionInfo */
#define API_ID_WdgM_GetVersionInfo      0x02u

/** API Service ID for WdgM_SetMode */
#define API_ID_WdgM_SetMode             0x03u

/** API Service ID for WdgM_GetMode */
#define API_ID_WdgM_GetMode             0x0bu

/** API Service ID for WdgM_GetLocalStatus */
#define API_ID_WdgM_GetLocalStatus      0x0cu

/** API Service ID for WdgM_GetGlobalStatus */
#define API_ID_WdgM_GetGlobalStatus     0x0du

/** API Service ID for WdgM_PerformReset */
#define API_ID_WdgM_PerformReset        0x0fu

/** API Service ID for WdgM_MainFunction */
#define API_ID_WdgM_MainFunction        0x08u

/** API Service ID for WdgM_DeactivateSupervisionEntity */
#define API_ID_WdgM_DeactivateSupervisionEntity   0x10u

/** API Service ID for WdgM_ActivateSupervisionEntity */
#define API_ID_WdgM_ActivateSupervisionEntity     0x11u

/* DET codes */
#define WDGM_E_NO_INIT                  0x10u
#define WDGM_E_PARAM_CONFIG             0x11u
#define WDGM_E_PARAM_MODE               0x12u
#define WDGM_E_PARAM_SEID               0x13u
#define WDGM_E_NULL_POINTER             0x14u
#define WDGM_E_DISABLE_NOT_ALLOWED      0x15u
#define WDGM_E_CPID                     0x16u
#define WDGM_E_DEPRECATED               0x17u
#define WDGM_E_TIMEBASE                 0x28u
#define WDGM_E_PARAM_STATE              0x29u
#define WDGM_E_WDGIF_MODE               0x2Au
#define WDGM_E_MEMORY_FAILURE           0x2Bu


/* Define a DET call for the GetVersionInfo macro implementation. */
#if (WDGM_DEV_ERROR_DETECT == STD_ON)
    #define WDGM_GETVERSION_DET_NULL_POINTER()        \
        Appl_Det_ReportError ( WDGM_MODULE_ID              \
                             , WDGM_VENDOR_ID              \
                             , API_ID_WdgM_GetVersionInfo  \
                             , WDGM_E_NULL_POINTER         \
                             )
#else
    #define WDGM_GETVERSION_DET_NULL_POINTER()
#endif /* (WDGM_DEV_ERROR_DETECT == STD_ON) */

/** Macro implementation of function WdgM_GetVersion() */
#if (WDGM_VERSION_INFO_API == STD_ON)
#define WdgM_GetVersionInfo(VersionInfoPtr)                              \
    {                                                                    \
        if((VersionInfoPtr) == NULL_PTR)                                     \
        {                                                                \
            WDGM_GETVERSION_DET_NULL_POINTER();                          \
        }                                                                \
        else                                                             \
        {                                                                \
            (VersionInfoPtr)->vendorID         = WDGM_VENDOR_ID;         \
            (VersionInfoPtr)->moduleID         = WDGM_MODULE_ID;         \
            (VersionInfoPtr)->sw_major_version = WDGM_SW_MAJOR_VERSION;  \
            (VersionInfoPtr)->sw_minor_version = WDGM_SW_MINOR_VERSION;  \
            (VersionInfoPtr)->sw_patch_version = WDGM_SW_PATCH_VERSION;  \
        }                                                                \
    } /* PRQA S 3458 */
#endif /* WDGM_VERSION_INFO_API == STD_ON */


/* ***************************************************************************
 * Diagnostic Event Manager (DEM) call macro
 *****************************************************************************/
/* PRQA S 3453 5 */
#if (WDGM_DEM_REPORT == STD_ON)
    #define WDGM_DEM_REPORTERROR(event_id,event_status) \
        Appl_Dem_ReportErrorStatus(event_id,event_status)
#else
    #define WDGM_DEM_REPORTERROR(event_id,event_status)
#endif /* WDGM_DEM_REPORT == STD_ON */

/* ***************************************************************************
 * Development Error Tracer (DET) call macro
 * WDGM301: all development errors shall be configurable
 *****************************************************************************/
/* PRQA S 3453 5 */
#if (WDGM_DEV_ERROR_DETECT == STD_ON)
    #define WDGM_DET_REPORTERROR(mod_id,ven_id,api_id,det_id)   \
        Appl_Det_ReportError(mod_id,ven_id,api_id,det_id)
#else
    #define WDGM_DET_REPORTERROR(mod_id,ven_id,api_id,det_id)
#endif /* (WDGM_DEV_ERROR_DETECT == STD_ON) */


/* ***************************************************************************
 * Externals
 *****************************************************************************/
 /* User defined functions for global interrupt disable/enable */
/* PRQA S 3210 1 */ /* PRQA S 3447 1 */
extern void GlobalSuspendInterrupts(void);
/* PRQA S 3210 1 */ /* PRQA S 3447 1 */
extern void GlobalRestoreInterrupts(void);

/* ***************************************************************************
 * Configuration Typedefs
 *****************************************************************************/


/* *****************************************************************************
 * General Macros
 ******************************************************************************/
/** Invalid checkpoint ID */
#define WDGM_INVALID_CP_ID              ((WdgM_CheckpointIdType) 0xFFFFu)
#define WDGM_INVALID_SE_ID              ((WdgM_SupervisedEntityIdType) 0xFFFFu)
#define WDGM_INVALID_TR_ID              ((WdgM_TransitionIdType) 0xFFFFu)
#define WDGM_INITIAL_TICK_COUNT         0x00000001ul
#define WDGM_INTERNAL_CP_TEST_OK        0x7931u
#define WDGM_INTERNAL_CP_TEST_NOK       0x0u

/* *****************************************************************************
 * S-WDGM API
 ******************************************************************************/
#if (WDGM_AUTOSAR_3_1_X_COMPATIBILITY != STD_ON)
/**
 *  Checkpoint reached functionality as defined by AUTOSAR 4.0 r1.
 *
 * @metric v(G)>10: the cyclomatic complexity is slightly higher because the
 *         function is implemented strictly according to its requirements.
 *         Splitting the function into more subfunctions than the current state
 *         would only damage the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 * @metric CALLS>7: the number of called functions is slightly higher because
 *         the function is split into several subfunctions to take over parts
 *         of its functionality. Taking some of the functionality back would
 *         increase other metrics such as cyclomatic complexity, number of
 *         paths, etc.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 * @metric LEVEL>4: the depth of nesting in this function is slightly higher
 *         than recommended because the function is implemented strictly
 *         according to its requirements. Any further splitting into
 *         subfunctions would only harm the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 *  @param SEID (in)             supervised entity ID
 *  @param CPID (in)             checkpoint ID
 *
 * @return an error-code
 *  @retval E_OK                 checkpoint reached successful
 *  @retval E_NOT_OK             checkpoint reached failed
 */
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_CheckpointReached
      ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
      , VAR (WdgM_CheckpointIdType, AUTOMATIC) CPID
      );

/**
 *  Selects a trigger mode.
 *
 * @metric RETURN>1: the number of points of return is higher than one. This is
 *         done in order to reduce the overal function complexity and increase
 *         the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 *  @param Mode (in)             new trigger mode ID to be set
 *  @param CallerId (in)         ID of the caller
 *
 * @return an error-code
 *  @retval E_OK                 new trigger mode selected successfully
 *  @retval E_NOT_OK             an error occurred
 */
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_SetMode
      (VAR (WdgM_ModeType, AUTOMATIC) Mode, VAR (uint16, AUTOMATIC) CallerID);
#else
  /* Update alive counter functionality as defined by AUTOSAR 3.1 */
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_UpdateAliveCounter
      (VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID);
  /* WdgM_SetMode declaration for AUTOSAR 3.1 */
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_SetMode
      (VAR (WdgM_ModeType, AUTOMATIC) Mode);
#endif /* (WDGM_AUTOSAR_3_1_X_COMPATIBILITY != STD_ON) */

/**
 *  Read a trigger mode.
 *
 *  @param Mode (in)             pointer to trigger mode
 *
 * @return an error-code
 *  @retval E_OK                 trigger mode returned successfully
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_GetMode
    (P2VAR (WdgM_ModeType, AUTOMATIC, WDGM_APPL_DATA) Mode);

/**
 *  Read local status of an Supervised Entity.
 *
 *  @param SEID (in)             Supervised Entity Identifier
 *  @param EntityStatus (in)     pointer to local entity status
 *
 * @return an error-code
 *  @retval E_OK                 local status returned successfully
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_GetLocalStatus
    ( VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID
    , P2VAR (WdgM_LocalStatusType, AUTOMATIC, WDGM_APPL_DATA) EntityStatus
    );

/**
 *  Read S-WdgM global status.
 *
 *  @param Status (in)           pointer to S-WdgM global status
 *
 * @return an error-code
 *  @retval E_OK                 global status returned successfully
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_GetGlobalStatus
    (P2VAR (WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) Status);

/**
 *  Perform an immediate MCU reset through the Watchdog.
 *
 *  @param (in/out)              void
 *
 * @return an error-code
 *  @retval E_OK                 immediate reset invoked sucessfully
 *  @retval E_NOT_OK             an error occurred
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (Std_ReturnType, WDGM_CODE) WdgM_PerformReset (void);


#if (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON)
/**
 *  Deactivate a supervised entity.
 *
 *  @param SEID (in)             Supervised Entity Identifier
 *
 * @return an error-code
 *  @retval E_OK                 an SE will be deactivated in next MainFunction
 *  @retval E_NOT_OK             an error occurred
 */
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_DeactivateSupervisionEntity
      (VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID);
/**
 *  Activate a supervised entity.
 *
 *  @param SEID (in)             Supervised Entity Identifier
 *
 * @return an error-code
 *  @retval E_OK                 a SE will be activated in next MainFunction
 *  @retval E_NOT_OK             an error occurred
 */
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (Std_ReturnType, WDGM_CODE) WdgM_ActivateSupervisionEntity
      (VAR (WdgM_SupervisedEntityIdType, AUTOMATIC) SEID);
#endif /* (WDGM_ENTITY_DEACTIVATION_ENABLED == STD_ON) */

/* *****************************************************************************
 * S-WDGM System API
 ******************************************************************************/

/* S-WdgM initialisation */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (void, WDGM_CODE) WdgM_Init
    (P2CONST (WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) WdgMConfigPtr);

/* S-WDGM Timebase Tick Counter */
#if (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK)
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (void, WDGM_CODE) WdgM_UpdateTickCount (void); /* PRQA S 1503 */
#else
 #if (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK)
  #if defined(WDGM_UNIT_TESTS)
   /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
   FUNC (void, WDGM_CODE) WdgM_UpdateTickCount (void); /* PRQA S 1503 */
  #endif /* (WDGM_UNIT_TESTS) */
 #endif /* (WDGM_TIMEBASE_SOURCE == WDGM_INTERNAL_SOFTWARE_TICK) */
#endif /* (WDGM_TIMEBASE_SOURCE == WDGM_EXTERNAL_TICK) */

/**
 *  Cyclic main function of the S-WdgM.
 *
 * @metric PATH>80: the calculated number of paths is above limits. The function
 *         is left that complex because it fulfills strictly the requirements;
 *         any attempt to split it into more subfunctions than now would only
 *         damage the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 * @metric v(G)>10: the cyclomatic complexity is slightly higher because the
 *         function is implemented strictly according to its requirements.
 *         Splitting the function into more subfunctions than the current state
 *         would only damage the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 * @metric CALLS>7: the number of called functions is slightly higher because
 *         the function is split into several subfunctions to take over parts
 *         of its functionality. Taking some of the functionality back would
 *         increase other metrics such as cyclomatic complexity, number of
 *         paths, etc.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 * @metric STMT>50: the number of instructions per function is above limits.
 *         Any attempt to split it into more subfunctions than now would only
 *         damage the code readability and increase the runtime.
 * @metric RETURN>1: the number of points of return is higher than one. This is
 *         done in order to reduce the overal function complexity and increase
 *         the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 * @return -
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (void, WDGM_CODE) WdgM_MainFunction (void);

/* *****************************************************************************
 * Module local functions, placed here for automatic unit tests
 ******************************************************************************/
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (void, WDGM_CODE) WdgM_SetTickCount
    (VAR (WdgM_TimeBaseTickType, AUTOMATIC) time_base_tick);
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC (WdgM_TimeBaseTickType, WDGM_CODE) WdgM_GetTickCount (void);
#if (WDGM_GLOBAL_TRANSITIONS == STD_ON)
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (void, WDGM_CODE) WdgM_WriteGlobalActivityFlag
      (VAR (WdgM_SharedBooleanType, AUTOMATIC) activity_flag);
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (void, WDGM_CODE) WdgM_WriteGlobalTransitionFlag
    ( VAR (WdgM_TransitionIdType, AUTOMATIC) global_tr_id
    , VAR (WdgM_SharedBooleanType, AUTOMATIC) new_value
    );
  /* PRQA S 3210 1 */ /* PRQA S 3408 1 */
  FUNC (WdgM_SharedBooleanType, WDGM_CODE) WdgM_ReadGlobalTransitionFlag
    ( VAR (WdgM_TransitionIdType, AUTOMATIC) global_tr_id
    , VAR (uint8, AUTOMATIC) clear_after_read
    );
#endif /* (WDGM_GLOBAL_TRANSITIONS == STD_ON) */

#endif /* _WDGM_H_ */
