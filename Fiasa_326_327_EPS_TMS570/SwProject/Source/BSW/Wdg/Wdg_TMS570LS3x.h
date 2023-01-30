/* Copyright (C) 2011-2012 TTTech Automotive GmbH. All rights reserved
** Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
**
** Name:
**   Wdg_TMS570LS3x.h
**
** Purpose: Header file for the TMS570LS3x specific implementation of the Safe
**          Watchdog Driver of the Modular Safety Platform.
**
*/

#ifndef WDG_TMS570LS3x_H_
#define WDG_TMS570LS3x_H_

/* ***************************************************************************
** Includes
******************************************************************************/
#include "Wdg_TMS570LS3x_Cfg.h"

/* ***************************************************************************
** Macros
******************************************************************************/
/* Published information */
#define WDG_TMS570LS3x_VENDOR_ID  46
#define WDG_TMS570LS3x_MODULE_ID  102

/* AUTOSAR release version */
#define WDG_TMS570LS3x_AR_RELEASE_MAJOR_VERSION     4
#define WDG_TMS570LS3x_AR_RELEASE_MINOR_VERSION     0
#define WDG_TMS570LS3x_AR_RELEASE_REVISION_VERSION  1

/* Module version */
#define WDG_TMS570LS3x_SW_MAJOR_VERSION  2
#define WDG_TMS570LS3x_SW_MINOR_VERSION  0
#define WDG_TMS570LS3x_SW_PATCH_VERSION  3

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(3:3210) The global identifier 'Wdg_TMS570LS3x_SetMode' /
                   'Wdg_TMS570LS3x_SetTriggerWindow' / 'Wdg_TMS570LS3x_Init' /
                   'Wdg_TMS570LS3x_GetVersionInfo'
                   is declared but is not used.
 * Justification : The function is the interface of this SW module to the upper
                   SW layers.                                                */

/* Error Message : Msg(4:3408) 'Wdg_TMS570LS3x_SetMode' /
                   'Wdg_TMS570LS3x_SetTriggerWindow' / 'Wdg_TMS570LS3x_Init' /
                   'Wdg_TMS570LS3x_GetVersionInfo'
                   has external linkage but is being defined without any
                   previous declaration.
 * Justification : The function is the interface of this SW module to the upper
                   SW layers and is declared in this header file.            */

/* Error Message : Msg(3:3210) The global identifier
                   'GlobalSuspendInterrupts' / 'GlobalRestoreInterrupts'
                   is declared but is not used.
 * Justification : This is a user defined function to suspend/restore
                   interrupts.                                               */

/* Error Message : Msg(4:3447) 'GlobalSuspendInterrupts' /
                   'GlobalRestoreInterrupts' has external linkage but this
                   declaration is not in a header file.
 * Justification : This file (Wdg_TMS570LS3x.h) is a header file.                       */

/* ***************************************************************************
** Prototypes
******************************************************************************/

/**
 * This service changes the TMS570LS3x internal watchdog's state and scales the
 * resets the watchdog according to the remaining time.
 *
 * metric  LEVEL>4: the depth of nesting in this function is slightly higher
 *         than recommended because the function is implemented strictly
 *         according to its requirements. Any further splitting into
 *         subfunctions would only harm the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 * detcodes
 * det        WDG_E_PARAM_MODE       Parameter WdgMode out of range
 * det        WDG_E_DRIVER_STATE     Wdg not initialized
 * demcodes
 * dem        WDG_E_MODE_FAILED      Changing the mode not successfull
 * dem        WDG_E_DISABLE_REJECTED Turning off the watchdog not allowed
 * param[in]  WdgInstance            Watchdog instnce (if several available)
 * param[in]  WdgMode                New mode for the watchdog
 * return     result
 * retval     E_OK                   service has completed without errors
 * retval     E_NOT_OK               an error has been detected
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_TMS570LS3x_SetMode
    (VAR (uint8, AUTOMATIC) WdgInstance, VAR (WdgIf_ModeType, AUTOMATIC) WdgMode);

/**
 * This service services, sets new timeout, and sets new window start for the
 * TMS570LS3x internal watchdog. It converts the provided time to watchdog ticks
 * according to the current watchdog mode.
 *
 * metric  v(G)>10: the cyclomatic complexity is slightly higher because the
 *         function is implemented strictly according to its requirements.
 *         Splitting the function into more subfunctions than the current state
 *         would only damage the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 * metric  LEVEL>4: the depth of nesting in this function is slightly higher
 *         than recommended because the function is implemented strictly
 *         according to its requirements. Any further splitting into
 *         subfunctions would only harm the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 * detcodes
 * det        WDG_E_PARAM_TIMEOUT    Parameter WindowStart or Timeout out of
 *                                    range (depends on watchdog frequency)
 * det        WDG_E_DRIVER_STATE     Wdg not initialized
 * demcodes
 * dem        WDG_E_MODE_FAILED      Changing the mode not successfull
 * dem        WDG_E_DISABLE_REJECTED Turning off the watchdog not allowed
 * param[in]  WdgInstance            Watchdog instnce (if several available)
 * param[in]  WindowStart            New window start time in [ms]
 * param[in]  Timeout                New timeout in [ms]
 * return     result
 * retval     E_OK                   service has completed without errors
 * retval     E_NOT_OK               an error has been detected
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_TMS570LS3x_SetTriggerWindow
    ( VAR (uint8, AUTOMATIC) WdgInstance
    , VAR (uint16, AUTOMATIC) WindowStart
    , VAR (uint16, AUTOMATIC) Timeout
    );

/**
 * This service initializes the TMS570LS3x internal watchdog.
 *
 * metric  v(G)>10: the cyclomatic complexity is slightly higher because the
 *         function is implemented strictly according to its requirements.
 *         Splitting the function into more subfunctions than the current state
 *         would only damage the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 * metric  STMT>50: the number of instructions per function is above limits.
 *         Any attempt to split it into more subfunctions than now would only
 *         damage the code readability and increase the runtime.
 *
 * metric  LEVEL>4: the depth of nesting in this function is slightly higher
 *         than recommended because the function is implemented strictly
 *         according to its requirements. Any further splitting into
 *         subfunctions would only harm the code readability.
 *         Furthermore, full test coverage is reached for this function as seen
 *         in the test report.
 *
 * detcodes
 * det        WDG_E_PARAM_CONFIG     Configuration pointer is NULL_PTR
 *
 * param[in]  ConfigPtr              A pointer to the configuration structure
 * return     result
 * retval     E_OK                   service has completed without errors
 * retval     E_NOT_OK               an error has been detected
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC(Std_ReturnType, WDG_CODE) Wdg_TMS570LS3x_Init
    (P2CONST(Wdg_TMS570LS3x_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);

#if (WDG_VERSION_INFO_API == STD_ON)
/**
 * This service returns the version information of the module.
 *
 * detcodes
 * det           WDG_E_PARAM_CONFIG Parameter VersionInfoPtr is NULL_PTR.
 * param[in/out] VersionInfoPtr  pointer to where to store the version info
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC(void, WDG_CODE) Wdg_TMS570LS3x_GetVersionInfo
    (P2VAR (Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) VersionInfoPtr);
#endif /* WDG_VERSION_INFO_API == STD_ON */

#if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
/**
 * This service returns the tick counter value.
 *
 * return    value of the tick counter
 */
/* PRQA S 3210 1 */ /* PRQA S 3408 1 */
FUNC(uint32, WDG_CODE) Wdg_TMS570LS3x_GetTickCounter (void);
#endif /* WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON */

/* ***************************************************************************
 * Externals
 *****************************************************************************/
 /* User defined functions for global interrupt disable/enable */
/* PRQA S 3210 1 */ /* PRQA S 3447 1 */
extern void GlobalSuspendInterrupts(void);
/* PRQA S 3210 1 */ /* PRQA S 3447 1 */
extern void GlobalRestoreInterrupts(void);

#endif /* WDG_TMS570LS3x_H_ */

