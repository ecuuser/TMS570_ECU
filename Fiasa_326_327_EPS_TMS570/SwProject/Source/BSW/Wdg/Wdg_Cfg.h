/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
** Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
**
** Name:
**   Wdg_Cfg.h
**
** Purpose: Provides platform dependent type declarations for the Safe
**          Watchdog Driver part of the Modular Safety Platform.
**
*/

#ifndef _WDG_CFG_H_
#define _WDG_CFG_H_

/* ***************************************************************************
** Includes
******************************************************************************/
#include "WdgIf_Types.h"
#include "WdgIf.h"

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(3:3205) The identifier 'Wdg_BasicConfigurationType'.
 * Justification : The identifier is used by the module source file and the
                   files containing the configuration.                       */

/* ***************************************************************************
** Macros
******************************************************************************/

/* AUTOSAR release version */
#define WDG_CFG_AR_MAJOR_VERSION     4
#define WDG_CFG_AR_MINOR_VERSION     0
#define WDG_CFG_AR_PATCH_VERSION     1

/* Module version */
#define WDG_CFG_SW_MAJOR_VERSION  2
#define WDG_CFG_SW_MINOR_VERSION  0
#define WDG_CFG_SW_PATCH_VERSION  1

#ifndef FALSE
    #error "Macro FALSE should be defined! ((boolean)0)"
#endif

#ifndef TRUE
    #error "Macro TRUE should be defined! ((boolean)1)"
#endif

#ifndef NULL_PTR
    #define NULL_PTR ((void *) 0)
#endif

/* ***************************************************************************
** Type definitions
******************************************************************************/

/**
 *  This type represents the S-Wdg configuration version.
 */
typedef uint8  Wdg_ConfigVersionType;

typedef struct {
    VAR(WdgIf_ModeType, AUTOMATIC) InitialMode; /**< Set Watchdog to this mode during
                                                     initialization */
    VAR(uint16, AUTOMATIC) InitialTimeout_ms; /**< Set Watchdog to this timeout during
                                                   initialization */
    VAR(uint16, AUTOMATIC) InitialWindowStart_ms; /**< Set Watchdog to this window
                                                       start during initialization */
    VAR(uint16, AUTOMATIC) SlowModeMax_ms; /**< Precalculated maximum period of the
                                                watchdog for the given FPI frequency
                                                for slow mode. Rounded down value. */
    VAR(uint16, AUTOMATIC) FastModeMax_ms; /**< Precalculated maximum period of the
                                                watchdog for the given FPI frequency
                                                for fast mode. Rounded down value. */


    /* Configuration Version */
    VAR(Wdg_ConfigVersionType, AUTOMATIC) WdgConfigMajorVersion;   /**< The same as S-Wdg Major version */
    VAR(Wdg_ConfigVersionType, AUTOMATIC) WdgConfigMinorVersion;   /**< The same as S-Wdg Minor version */
/* PRQA S 3205 1 */
} Wdg_BasicConfigurationType;

#endif /* _WDG_CFG_H_ */
