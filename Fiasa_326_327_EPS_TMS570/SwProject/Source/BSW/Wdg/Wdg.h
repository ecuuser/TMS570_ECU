/* Copyright (C) 2010-2012 TTTech Automotive GmbH. All rights reserved
** Schoenbrunnerstrasse 7, A-1040 Wien, Austria. office(at)tttech-automotive.com
**
** Name:
**   Wdg.h
**
** Purpose: Common include file for the Safe Watchdog Driver.
**
*/

#ifndef _WDG_H_
#define _WDG_H_

/* ***************************************************************************
** Includes
******************************************************************************/
#include "Wdg_Cfg.h"

/* ***************************************************************************
** Macros
******************************************************************************/

/* AUTOSAR release version */
#define WDG_AR_MAJOR_VERSION     4
#define WDG_AR_MINOR_VERSION     0
#define WDG_AR_PATCH_VERSION     1

/* Module version */
#define WDG_SW_MAJOR_VERSION  2
#define WDG_SW_MINOR_VERSION  0
#define WDG_SW_PATCH_VERSION  2

/* Published information */
#define WDG_VENDOR_ID  46u
#define WDG_MODULE_ID  102u

/** API Service ID for Wdg_Init */
#define API_ID_Wdg_Init                0x00u

/** API Service ID for Wdg_SetMode */
#define API_ID_Wdg_SetMode             0x01u

/** API Service ID for Wdg_SetTriggerCondition */
#define API_ID_Wdg_SetTriggerCondition 0x03u

/** API Service ID for Wdg_GetVersionInfo */
#define API_ID_Wdg_GetVersionInfo      0x04u

/** API Service ID for Wdg_SetTriggerWindow */
#define API_ID_Wdg_SetTriggerWindow    0x06u

/** API Service ID for Wdg_GetTickCounter */
#define API_ID_Wdg_GetTickCounter      0x07u

/* DET codes */
#define WDG_E_DRIVER_STATE   0x10u
#define WDG_E_PARAM_MODE     0x11u
#define WDG_E_PARAM_CONFIG   0x12u
#define WDG_E_PARAM_TIMEOUT  0x13u
#define WDG_E_SEQ_STATE      0x14u

#endif /* _WDG_H_ */
