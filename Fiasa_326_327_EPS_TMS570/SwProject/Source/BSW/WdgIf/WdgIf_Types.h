/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name:
 *   WdgIf_Types.h
 *
 * Purpose: Provides type declarations for the Safe Watchdog Interface part of
 *          the Modular Safety Platform.
 *
 */

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(3:3205) The identifier 'WdgIf_ModeType' is not
                   used and could be removed.
 * Justification : The identifier is used at least by the module source file
                   and the files containing the configuration.               */

#ifndef _WDGIF_TYPES_H_
#define _WDGIF_TYPES_H_

/* ***************************************************************************
** Includes
******************************************************************************/
#include "Std_Types.h"

/* ***************************************************************************
** Macros
******************************************************************************/
/*
   Macros STD_ON, STD_OFF, E_OK, E_NOT_OK must be defined in Std_Types.h and
   are implicitly included here. Their existence and values are, however,
   checked according to the Safe Watchdog Stack requirements.
*/
#if (! defined STD_ON)
    #error "Safe Watchdog Stack requires the macro 'STD_ON' to be defined as 1."
#endif

#if (! defined STD_OFF)
    #error "Safe Watchdog Stack requires the macro 'STD_OFF' to be defined as 0."
#endif

#if (! defined E_OK)
    #error "Safe Watchdog Stack requires the macro 'E_OK' to be defined as 0."
#endif

#if (! defined E_NOT_OK)
    #error "Safe Watchdog Stack requires the macro 'E_NOT_OK' to be defined as 1."
#endif

/* ***************************************************************************
** Type definitions
******************************************************************************/
/**< Mode for the Watchdog Interface */
typedef enum {
      WDGIF_OFF_MODE  = 0  /**< Watchdog disabled */
    , WDGIF_SLOW_MODE = 1  /**< Long timeout period (slow triggering) */
    , WDGIF_FAST_MODE = 2  /**< Short timeout period (fast triggering) */
} WdgIf_ModeType; /* PRQA S 3205 */

/* ***************************************************************************
** Prototypes
******************************************************************************/

#endif /* _WDGIF_TYPES_H_ */
