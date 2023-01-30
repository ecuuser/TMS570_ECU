/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
 * Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
 *
 * Name:
 *   WdgIf_Types.h
 *
 * Purpose: Provides platform independent type declarations for the Safe
 *          Watchdog Interface part of the Modular Safety Platform.
 *
 */

/* ------------------------------------------------------------------------- */
/*                        SUPRESSED MISRA VIOLATONS                          */
/* ------------------------------------------------------------------------- */
/* Error Message : Msg(3:3205) The identifier 'WdgIf_BasicConfigurationType' /
                   'WdgIf_InterfaceType' is not used and could be removed.
 * Justification : The identifier is used by the module source file and the
                   files containing the configuration.                       */

#ifndef _WDGIF_CFG_H_
#define _WDGIF_CFG_H_

/* ***************************************************************************
** Includes
******************************************************************************/
#include "Std_Types.h"
#include "WdgIf_Types.h"

/* Generated or provided by the user - preprocessor options for module features */
#include "WdgIf_Cfg_Features.h"

/* ***************************************************************************
** Macros
******************************************************************************/

#ifndef WDGIF_DEV_ERROR_DETECT
    #error "Macro WDGIF_DEV_ERROR_DETECT should be defined! (ON/OFF)"
#endif

#ifndef WDGIF_INTERNAL_TICK_COUNTER
        #error "Macro WDGIF_INTERNAL_TICK_COUNTER should be defined! (ON/OFF)"
#endif

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

typedef struct {
    P2FUNC (Std_ReturnType, WDGIF_CODE, Wdg_SetMode)
        (VAR (uint8, AUTOMATIC), VAR (WdgIf_ModeType, AUTOMATIC));
    P2FUNC (Std_ReturnType, WDGIF_CODE, Wdg_SetTriggerWindow)
        (VAR (uint8, AUTOMATIC), VAR (uint16, AUTOMATIC), VAR (uint16, AUTOMATIC));
} WdgIf_InterfaceFunctionsType;

typedef struct {
    P2CONST (WdgIf_InterfaceFunctionsType, WDGIF_CONST, WDGIF_APPL_CONST) WdgFunctions;
    VAR (uint8, AUTOMATIC) WdgInstance;
} WdgIf_InterfaceFunctionsPerWdgDeviceType;

typedef struct {
    VAR (uint8, AUTOMATIC) NumOfWdgs;
#ifndef WDGIF_UNIT_TESTS
    P2CONST (WdgIf_InterfaceFunctionsPerWdgDeviceType, WDGIF_CONST, WDGIF_APPL_CONST) WdgFunctionsPerDevice;
#else
    P2VAR   (WdgIf_InterfaceFunctionsPerWdgDeviceType, WDGIF_VAR, WDGIF_APPL_DATA) WdgFunctionsPerDevice;
#endif
#if (WDGIF_INTERNAL_TICK_COUNTER == STD_ON)
    /* Function pointer to the GetTickCounter driver function */
    P2FUNC (uint32, WDGIF_CODE, Wdg_GetTickCounter) (void);
#endif /* (WDGIF_INTERNAL_TICK_COUNTER == STD_ON) */

/* PRQA S 3205 1 */
} WdgIf_InterfaceType;

/* ***************************************************************************
** Prototypes
******************************************************************************/

#endif /* _WDGIF_CFG_H_ */
