/* Copyright (C) 2011-2012 TTTech Automotive GmbH. All rights reserved
** Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
**
** Name:
**   Wdg_TMS570LS3x_Cfg.h
**
** Purpose: Declarations for the TMS570LS3x specific configuration of the Safe
**          Watchdog Driver part of the Modular Safety Platform.
**
*/

#ifndef WDG_TMS570LS3x_CFG_H_
#define WDG_TMS570LS3x_CFG_H_

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(4:3332) The macro 'WDG_USE_OS_SUSPEND_INTERRUPT'
                   used in this '#if...' test is not defined.
 * Justification : This file 'Wdg_TMS570LS3x_Cfg.h' includes explicitly
                   'Wdg_TMS570LS3x_Cfg_Features.h' which defines
                   'WDG_USE_OS_SUSPEND_INTERRUPT'. Furthermore there is an
                   explicit check (in 'Wdg_TMS570LS3x_Cfg.h') whether
                   'WDG_USE_OS_SUSPEND_INTERRUPT' is defined at all.         */

/* ***************************************************************************
** Includes
******************************************************************************/
#include "Wdg.h"

/* Generated or provided by the user - preprocessor options for module features */
#include "Wdg_TMS570LS3x_Cfg_Features.h"

/* ***************************************************************************
** Macros
******************************************************************************/

/* Module version */
#define WDG_TMS570LS3x_CFG_SW_MAJOR_VERSION  2
#define WDG_TMS570LS3x_CFG_SW_MINOR_VERSION  0
#define WDG_TMS570LS3x_CFG_SW_PATCH_VERSION  3

/* Common driver options */
#ifndef WDG_DISABLE_ALLOWED
    #error "Macro WDG_DISABLE_ALLOWED should be defined! (ON/OFF)"
#endif

#ifndef WDG_DEV_ERROR_DETECT
    #error "Macro WDG_DEV_ERROR_DETECT should be defined! (ON/OFF)"
#endif

#ifndef WDG_DEM_REPORT
    #error "Macro WDG_DEM_REPORT should be defined! (ON/OFF)"
#endif

#ifndef WDG_USE_OS_SUSPEND_INTERRUPT
    #error "Macro WDG_USE_OS_SUSPEND_INTERRUPT should be defined! (ON/OFF)"
#endif

/* TMS570LS3x specific options */
#if (WDG_DISABLE_ALLOWED != STD_OFF)
    #error "TMS570LS3x does not support watchdog disabling. WDG_DISABLE_ALLOWED must be set to STD_OFF."
#endif

#ifndef WDG_TMS570LS3x_INTERNAL_TICK_COUNTER     /*name of the switch still tbd*/
    #error "Macro WDG_TMS570LS3x_INTERNAL_TICK_COUNTER     should be defined! (ON/OFF)"
#endif

/* PRQA S 3332 1 */
#if (WDG_USE_OS_SUSPEND_INTERRUPT == STD_ON)
  /* Use Schedule Manager to disable/restore interrupts */
  #include "SchM_Wdg.h"
  #define Wdg_GlobalSuspendInterrupts()   SchM_Enter_Wdg_TMS570LS3x(WDG_TMS570LS3x_EXCLUSIVE_AREA_0)
  #define Wdg_GlobalRestoreInterrupts()   SchM_Exit_Wdg_TMS570LS3x(WDG_TMS570LS3x_EXCLUSIVE_AREA_0)
#else
  /* User defined functions for global interrupt disable/enable */
  #define Wdg_GlobalSuspendInterrupts()   GlobalSuspendInterrupts()
  #define Wdg_GlobalRestoreInterrupts()   GlobalRestoreInterrupts()
#endif /* (WDG_USE_OS_SUSPEND_INTERRUPT == STD_ON) */

/* ***************************************************************************
** Type definitions
******************************************************************************/
/**
 *  This type represents the configuration checksum for the TMS570LS3x S-Wdg.
 */
typedef uint32 Wdg_TMS570LS3x_ConfigChecksumType;

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(3:3205) The identifier 'Wdg_TMS570LS3x_ConfigType' is not
                   used and could be removed.
 * Justification : The identifier is used by the module source file and the
                   files containing the configuration.                       */

/** Platform specific configuration stucture for the TMS570LS3x Watchdog */
typedef struct {
    const Wdg_BasicConfigurationType *BasicCfgPtr; /**< Pointer to the
                                                          platform independent
                                                          settings */
    uint32 RTICLK_khz; /**< RTI frequency in kHz, for calculating ms / Wdg ticks */
    #if (WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON)
    uint32 TickFreq_hz; /**< Required ticks per second for the WdgM */
    #endif /* WDG_TMS570LS3x_INTERNAL_TICK_COUNTER == STD_ON */
    Wdg_TMS570LS3x_ConfigChecksumType ConfigChecksum; /**< Checksum over the
                                                        configuration */
} Wdg_TMS570LS3x_ConfigType; /* PRQA S 3205 */

/* ***************************************************************************
** Prototypes
******************************************************************************/

#endif /* WDG_TMS570LS3x_CFG_H_ */

